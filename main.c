/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:21:30 by mquero            #+#    #+#             */
/*   Updated: 2024/12/15 20:57:50 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char *argv, char **envp)
{
    int i;
    char **paths;
    char *wholepath;

    i = 0;
    while (envp[i])
    {
        if (envp[i][0] == 'P' && envp[i][1] == 'A' && envp[i][2] == 'T')
            paths = ft_split(envp[i] + 5, ':');
        i++;
    }
    i = 0;
    while (paths[i])
    {
        wholepath = ft_strjoin(paths[i], argv);
        if (access(wholepath, X_OK) == 0)
            break;
        else
            free(wholepath);
        i++;
    }
    freesplit(paths);
    return (wholepath);
}

void    child1(t_fd fd, char **argv, char **envp)
{
    char    *path;
    char    **split;

    path = find_path(argv[2], envp);
    split = ft_split(argv[2], ' ');
    dup2(fd.input, STDIN_FILENO);
    dup2(fd.pipe[1], STDOUT_FILENO);
    close(fd.input);
    close(fd.output);
    close(fd.pipe[0]);
    close(fd.pipe[1]);
    execve(path, split, envp);
    free(path);
    freesplit(split);
}
void    child2(t_fd fd, char **argv, char **envp)
{
    char    *path;
    char    **split;

    path = find_path(argv[3], envp);
    split = ft_split(argv[3], ' ');
    dup2(fd.pipe[0], STDIN_FILENO);
    dup2(fd.output, STDOUT_FILENO);
    close(fd.input);
    close(fd.output);
    close(fd.pipe[0]);
    close(fd.pipe[1]);
    execve(path, split, envp);
    freesplit(split);
    free(path);
}

int	main(int argc, char **argv, char **envp)
{
    t_fd    fd;
	int		pid1;
	int		pid2;

    if (argc != 5)
    {
        return 0;
    }
	pipe(fd.pipe);
	fd.input = open(argv[1], O_RDONLY);
	fd.output = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	pid1 = fork();
	if (pid1 == 0)
        child1(fd, argv, envp);
	pid2 = fork();
	if (pid2 == 0)
        child2(fd, argv, envp);
    close(fd.pipe[0]);
    close(fd.pipe[1]);
    close(fd.output);
    close(fd.input);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
	return (0);
}
