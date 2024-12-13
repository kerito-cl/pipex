/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:21:30 by mquero            #+#    #+#             */
/*   Updated: 2024/12/13 15:02:05 by mquero           ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	char	buffer[10000];
	int		pid1;
	int		pid2;
	int i = 0;
    char    *path1;
    char    *path2;
    char    **split;
    int fd_input;
    int fd_output;

	(void) argc;
	pipe(fd);
    path1 = find_path(argv[2], envp);
    if (argc > 3)
        path2 = find_path(argv[3], envp);
    split = ft_split(argv[2], ' ');

	fd_input = open(argv[1], O_RDONLY);
	fd_output = open(argv[4], O_WRONLY | O_APPEND | O_CREAT, 0644);
	pid1 = fork();
	pid2 = fork();
	if (pid1 == 0)
	{
	    dup2(fd[0], 0);
        close(fd[0]);
        close(fd[1]);
	    execve(path1, split, envp);
		/*read(fd[0], buffer, 10000);
		write(fd[1], buffer , 100);
		close(fd[0]);
		close(fd[1]);*/
	}

    close(fd[0]);
	if (pid2 == 0)
	{
	    dup2(fd[1], 1);
        close(fd[1]);
    }
	dup2(fd[1], 1);
	pid2 = fork();
	close(fd[1]);
	close(fd[0]);
	return (0);
}
