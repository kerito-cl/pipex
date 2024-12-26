/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:50:40 by mquero            #+#    #+#             */
/*   Updated: 2024/12/26 14:05:51 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./printf/ft_printf.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_fd
{
	int		pipe[2];
	char	*path1;
	char	*path2;
	char	**split;
	int		input;
	int		output;
	int		status;
}			t_fd;

char		*ft_strjoin(char const *s1, char const *s2);
void		freesplit(char **strs);
char		**ft_split(char const *s, char c);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
char		*ft_strdup(const char *s);
void		child1(t_fd fd, char **argv, char **envp);
void		child2(t_fd fd, char **argv, char **envp);
void		close_all(t_fd *fd);
void		throw_error_child1(char *path, char *str, t_fd *fd, char *arg);
void		throw_error_child2(char *path, t_fd *fd, char *arg);
void		error_ifdir(char *str);

#endif