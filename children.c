/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 11:10:55 by mquero            #+#    #+#             */
/*   Updated: 2024/12/26 14:05:42 by mquero           ###   ########.fr       */
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

char	*find_path(char *argv, char **envp, int i)
{
	char	**paths;
	char	*wholepath;

	while (envp[i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A' && envp[i][2] == 'T'
		&& envp[i][3] == 'H' && envp[i][4] == '=')
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
	split = ft_split(argv[2], ' ');
	if (check_if_full_path(split[0]))
		path = ft_strdup(split[0]);
	else
		path = find_path(argv[2], envp, i);
	if (path == NULL || fd.input == -1)
	{
		freesplit(split);
		throw_error_child1(path, argv[1], &fd, argv[2]);
	}
	dup2(fd.input, STDIN_FILENO);
	dup2(fd.pipe[1], STDOUT_FILENO);
	close_all(&fd);
	if (execve(path, split, envp) == -1)
	{
		freesplit(split);
		perror(path);
		free(path);
		exit (1);
	}
}

void	child2(t_fd fd, char **argv, char **envp)
{
	char	*path;
	char	**split;
	int		i;

	i = 0;
	split = ft_split(argv[3], ' ');
	if (check_if_full_path(split[0]))
		path = ft_strdup(split[0]);
	else
		path = find_path(argv[3], envp, i);
	if (path == NULL)
	{
		freesplit(split);
		throw_error_child2(path, &fd, argv[3]);
	}
	dup2(fd.pipe[0], STDIN_FILENO);
	dup2(fd.output, STDOUT_FILENO);
	close_all(&fd);
	if (execve(path, split, envp) == -1)
	{
		perror(path);
		free(path);
		freesplit(split);
		exit(126);
	}
}
