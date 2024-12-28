/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:21:30 by mquero            #+#    #+#             */
/*   Updated: 2024/12/28 14:56:12 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_fd	fd;

	if (argc != 5)
	{
		write(2, "Bad arguments", 13);
		return (1);
	}
	pipe(fd.pipe);
	fd.input = open(argv[1], O_RDONLY);
	if (fd.input == -1)
		error_ifdir(argv[1]);
	fd.output = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd.output == -1)
		error_ifdir(argv[4]);
	fd.pid1 = fork();
	if (fd.pid1 == 0)
		child1(fd, argv, envp);
	fd.pid2 = fork();
	if (fd.pid2 == 0)
		child2(fd, argv, envp);
	close_all(&fd);
	waitpid(fd.pid1, NULL, 0);
	waitpid(fd.pid2, &fd.status, 0);
	exit(WEXITSTATUS(fd.status));
}
