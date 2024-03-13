/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:58:08 by gneto-co          #+#    #+#             */
/*   Updated: 2024/03/11 15:01:46 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	process1(t_data *d)
{
	int	infile_fd;

	// open child process
	d->pid1 = fork();
	if (d->pid1 < 0)
		return (2);
	// execute if process is a child
	if (d->pid1 == 0)
	{
		// open infile to read only
		infile_fd = open(d->infile, O_RDONLY);
		if (infile_fd == -1)
		{
			perror("open");
			ft_free_data(d);
			close(d->fd[0]);
			close(d->fd[1]);
			exit(21);
		}
		// put infile instead of std input
		// and fd[1] instead of std output
		dup2(infile_fd, STDIN_FILENO);
		dup2(d->fd[1], STDOUT_FILENO);
		// close all because it is what it is
		close(infile_fd);
		close(d->fd[0]);
		close(d->fd[1]);
		// exe command
		execve(d->cmd1, d->args1, NULL);
		// error management
		perror("execve");
		exit(EXIT_FAILURE);
	}
	return (0);
}

int	process2(t_data *d)
{
	int	outfile_fd;

	// open child process
	d->pid2 = fork();
	if (d->pid2 < 0)
		return (30);
	// execute if process is a child
	if (d->pid2 == 0)
	{		outfile_fd = open(d->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);

		// put fd[0] instead of std input
		dup2(d->fd[0], STDIN_FILENO);
		// close all because it is what it is
		close(d->fd[0]);
		close(d->fd[1]);
		// open outfile
		outfile_fd = open(d->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (outfile_fd == -1)
		{
			perror("open");
			close(STDIN_FILENO);
			ft_free_data(d);
			close(d->fd[0]);
			close(d->fd[1]);
			exit(31);
		}
		// put outfile instead of std output
		dup2(outfile_fd, STDOUT_FILENO);
		close(outfile_fd);
		// execute command
		execve(d->cmd2, d->args2, NULL);
		// error management
		perror("execve");
		exit(EXIT_FAILURE);
	}
	return (0);
}
