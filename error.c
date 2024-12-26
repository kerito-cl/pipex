/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 11:13:12 by mquero            #+#    #+#             */
/*   Updated: 2024/12/26 14:06:54 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_all(t_fd *fd)
{
	close(fd->pipe[0]);
	close(fd->pipe[1]);
	if (fd->output != -1)
		close(fd->output);
	if (fd->input != -1)
		close(fd->input);
}

void	throw_error_child1(char *path, char *str, t_fd *fd, char *arg)
{
	if (fd->input == -1)
		perror(str);
	else if (path == NULL)
		ft_printf("pipex: command not found: %s\n", arg);
	if (path != NULL)
	{
		free(path);
	}
	close_all(fd);
	exit(1);
}

void	throw_error_child2(char *path, t_fd *fd, char *arg)
{
	if (path == NULL)
		ft_printf("pipex: command not found: %s\n", arg);
	if (path != NULL)
	{
		free(path);
	}
	close_all(fd);
	exit(127);
}

void	error_ifdir(char *str)
{
	ft_printf("pipex: Is a directory: %s\n", str);
	exit(1);
}
