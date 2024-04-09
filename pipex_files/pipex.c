/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:58:08 by gneto-co          #+#    #+#             */
/*   Updated: 2024/04/09 10:36:51 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_pipe(t_data *d)
{
	close(d->fd[0]);
	close(d->fd[1]);
}

static void	p1_spl(t_data *d, int *infile_fd)
{
	dup2((*infile_fd), STDIN_FILENO);
	dup2(d->fd[1], STDOUT_FILENO);
	close(*infile_fd);
	close_pipe(d);
}

int	process1(t_data *d)
{
	int	infile_fd;

	d->pid1 = fork();
	if (d->pid1 < 0)
		return (1);
	if (d->pid1 == 0)
	{
		infile_fd = open(d->infile, O_RDONLY);
		if (infile_fd == -1)
		{
			perror("open");
			ft_free_data(d);
			close_pipe(d);
			exit(1);
		}
		p1_spl(d, &infile_fd);
		if (execve(d->cmd1, d->args1, NULL) < 0)
		{
			perror("execve");
			ft_free_data(d);
			exit(1);
		}
		exit(EXIT_FAILURE);
	}
	return (0);
}

static int	p2_spl(t_data *d)
{
	if (execve(d->cmd2, d->args2, NULL) < 0)
	{
		perror("execve");
		ft_free_data(d);
		return (1);
	}
	return (0);
}

int	process2(t_data *d)
{
	int	outfile_fd;

	d->pid2 = fork();
	if (d->pid2 < 0)
		return (1);
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
			exit(1);
		}
		dup2(outfile_fd, STDOUT_FILENO);
		close(outfile_fd);
		if (p2_spl(d))
			exit(1);
		exit(EXIT_FAILURE);
	}
	return (0);
}
