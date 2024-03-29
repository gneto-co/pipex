/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:58:08 by gneto-co          #+#    #+#             */
/*   Updated: 2024/03/21 12:40:09 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_pipe(t_data *d)
{
	close(d->fd[0]);
	close(d->fd[1]);
}

int	process1(t_data *d)
{
	int	infile_fd;

	d->pid1 = fork();
	if (d->pid1 < 0)
		return (2);
	if (d->pid1 == 0)
	{
		infile_fd = open(d->infile, O_RDONLY);
		if (infile_fd == -1)
		{
			perror("open");
			ft_free_data(d);
			close_pipe(d);
			exit(21);
		}
		dup2(infile_fd, STDIN_FILENO);
		dup2(d->fd[1], STDOUT_FILENO);
		close(infile_fd);
		close_pipe(d);
		execve(d->cmd1, d->args1, NULL);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	return (0);
}

int	process2(t_data *d)
{
	int	outfile_fd;

	d->pid2 = fork();
	if (d->pid2 < 0)
		return (30);
	if (d->pid2 == 0)
	{
		dup2(d->fd[0], STDIN_FILENO);
		close_pipe(d);
		outfile_fd = open(d->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (outfile_fd == -1)
		{
			perror("open");
			close(STDIN_FILENO);
			ft_free_data(d);
			close_pipe(d);
			exit(31);
		}
		dup2(outfile_fd, STDOUT_FILENO);
		close(outfile_fd);
		execve(d->cmd2, d->args2, NULL);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	return (0);
}
