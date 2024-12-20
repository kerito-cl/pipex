/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 11:13:12 by mquero            #+#    #+#             */
/*   Updated: 2024/12/20 12:55:19 by mquero           ###   ########.fr       */
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
	if (fd->if_dir != -1)
		close(fd->if_dir);
}

void	throw_error_child1(char *path, char *str, t_fd *fd, char *arg)
{
	if (fd->input == -1)
		perror(str);
	else if (path == NULL)
		ft_printf("command not found: %s\n", arg);
	if (path != NULL)
	{
		free(path);
	}
	close_all(fd);
	exit(1);
}

void	throw_error_child2(char *path, char *str, t_fd *fd, char *arg)
{
	if (fd->if_dir != -1)
		ft_printf("Is a directory: %s\n", str);
	else if (path == NULL)
		ft_printf("command not found: %s\n", arg);
	if (path != NULL)
	{
		free(path);
	}
	close_all(fd);
	exit(1);
}
