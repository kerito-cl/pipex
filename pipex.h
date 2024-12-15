/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:50:40 by mquero            #+#    #+#             */
/*   Updated: 2024/12/15 16:54:46 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <limits.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
#include <sys/wait.h>


typedef struct s_fd
{
	int		pipe[2];
	char	buffer[10000];
    char    *path1;
    char    *path2;
    char    **split;
    int input;
    int output;
}   t_fd;


char	*ft_strjoin(char const *s1, char const *s2);
void	freesplit(char **strs);
char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

#endif