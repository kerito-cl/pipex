/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:21:30 by mquero            #+#    #+#             */
/*   Updated: 2024/12/18 16:53:19 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool	check_if_full_path(char *arg)
{
		if (access(arg, X_OK) == 0)
			return (true);
		else
			return (false);
}


void	close_all(t_fd *fd)
{
	close(fd->pipe[0]);
	close(fd->pipe[1]);
	close(fd->output);
	close(fd->input);
}

void	throw_error(char *path,char *str, t_fd *fd)
{
	if (fd->input == -1)
        perror(str);
	else if (path == NULL)
        perror("command not found");
	close_all(fd);
	exit(1);
}

char	*find_path(char *argv, char **envp, int i)
{
	char	**paths;
	char	*wholepath;

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
			break ;
		else
		{
			free(wholepath);
			wholepath = NULL;
		}
		i++;
	}
	freesplit(paths);
	return (wholepath);
}

void	child1(t_fd fd, char **argv, char **envp)
{
	char	*path;
	char	**split;
	int		i;

	i = 0;
	if (check_if_full_path(argv[2]))
		path = ft_strdup(argv[2]);
	else
		path = find_path(argv[2], envp, i);
	if (path == NULL || fd.input == -1)
		throw_error(path, argv[1], &fd);
	split = ft_split(argv[2], ' ');
	dup2(fd.input, STDIN_FILENO);
	dup2(fd.pipe[1], STDOUT_FILENO);
	close_all(&fd);
	if (execve(path, split, envp) == -1)
    {
        freesplit(split);
        perror(path);
        free(path);
        exit(1);
    }
}

void	child2(t_fd fd, char **argv, char **envp)
{
	char	*path;
	char	**split;
	int		i;

	i = 0;
	if (check_if_full_path(argv[3]))
		path = ft_strdup(argv[3]);
	else
		path = find_path(argv[3], envp, i);
	if (path == NULL)
	{
		perror(argv[3]);
		exit(1);
	}
	split = ft_split(argv[3], ' ');
	dup2(fd.pipe[0], STDIN_FILENO);
	dup2(fd.output, STDOUT_FILENO);
	close_all(&fd);
	if (execve(path, split, envp) == -1)
    {
        perror(path);
		free(path);
		freesplit(split);
		exit(1);
    }
}

int	main(int argc, char **argv, char **envp)
{
	t_fd	fd;
	int		pid1;
	int		pid2;

	if (argc != 5)
		return (0);
	pipe(fd.pipe);
	fd.input = open(argv[1], O_RDONLY);

	fd.output = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	pid1 = fork();
	if (pid1 == 0)
		child1(fd, argv, envp);
	pid2 = fork();
	if (pid2 == 0)
		child2(fd, argv, envp);
	close_all(&fd);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
