/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:21:30 by mquero            #+#    #+#             */
/*   Updated: 2024/12/10 13:17:56 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char **argv, char **env)
{
    int fd[2];
    char   buffer[10000];
    
    (void) argc;
    fd[0] = open(argv[1], O_RDONLY);
    fd[1] = open(argv[4], O_WRONLY | O_APPEND | O_CREAT, 0644);
    //pipe(fd);

        read(fd[0], buffer, 10000);
        printf("%s", buffer);
    int  i = 0;
        while (buffer[i])
        {
            write(fd[1], &buffer[i], 1);
            i++;
        }
    /*int id = fork();
    int  i = 0;
    if (id == 0)
    {
        close(fd[0]);
        while (buffer[i])
        {
            write(fd[1], &buffer[i], 1);
            i++;
        }
        close(fd[1]);
    }
    else
    {
        close(fd[1]);
        read(fd[0], buffer, 10000);
        printf("%s", buffer);
        close(fd[0]);
    }*/

    /*while (env[i])
    {
        printf("%s\n",env[i]);
        i++;
    }
    printf("%s\n",env[36]);*/
    /*execve("/usr/bin/cat", argv, env);
    printf("execve failed");*/
    return 0;
}
