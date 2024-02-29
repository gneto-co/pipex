/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:58:08 by gneto-co          #+#    #+#             */
/*   Updated: 2024/02/29 16:03:44 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int process1(t_data *d)
{
    d->pid1 = fork();
    if (d->pid1 < 0)
        return 2;

    if (d->pid1 == 0) {
        // child process 1
        dup2(d->fd[1], STDOUT_FILENO);
        close(d->fd[0]);
        close(d->fd[1]);
        
        execve(d->cmd1, d->args1, NULL);
        
        // Se execve() retornar, algo deu errado
        perror("execve");
        exit(EXIT_FAILURE);
    }
}

int process2(t_data *d)
{
    d->pid2 = fork();
    if (d->pid2 < 0)
        return 3;

    if (d->pid2 == 0) {
        // child process 2
        dup2(d->fd[0], STDIN_FILENO);
        close(d->fd[0]);
        close(d->fd[1]);
        
		int outfile_fd = open(d->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (outfile_fd == -1) {
            perror("open");
            return 5;
        }
        dup2(outfile_fd, STDOUT_FILENO);
		
        execve(d->cmd2, d->args2, NULL);
        
        // Se execve() retornar, algo deu errado
        perror("execve");
        exit(EXIT_FAILURE);
    }
}
