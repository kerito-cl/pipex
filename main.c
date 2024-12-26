/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:21:30 by mquero            #+#    #+#             */
/*   Updated: 2024/12/26 14:05:00 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_fd	fd;
	int		pid1;
	int		pid2;

	if (argc != 5)
	{
		write(2, "Bad arguments", 13);
		return (1);
	}
	pipe(fd.pipe);
	fd.output = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd.output == -1)
		error_ifdir(argv[4]);
	fd.input = open(argv[1], O_RDONLY);
	pid1 = fork();
	if (pid1 == 0)
		child1(fd, argv, envp);
	pid2 = fork();
	if (pid2 == 0)
		child2(fd, argv, envp);
	close_all(&fd);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &fd.status, 0);
	exit(WEXITSTATUS(fd.status));
}
