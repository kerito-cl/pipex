/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:50:40 by mquero            #+#    #+#             */
/*   Updated: 2024/12/18 13:59:16 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <limits.h>
# include <stdint.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
#include <string.h>
#include <errno.h>


typedef struct s_fd
{
	int		pipe[2];
	char	*path1;
	char	*path2;
	char	**split;
	int		input;
	int		output;
}			t_fd;

char		*ft_strjoin(char const *s1, char const *s2);
void		freesplit(char **strs);
char		**ft_split(char const *s, char c);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strdup(const char *s);

#endif