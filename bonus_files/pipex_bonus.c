/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:58:08 by gneto-co          #+#    #+#             */
/*   Updated: 2024/03/13 17:36:02 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
int	process(t_data *d, int i)
{
	int	infile_fd;
	int	outfile_fd;

// open pipe

	if (pipe((d->p[i]).fd) == -1)
			return -1;

// open child process

	(d->p[i]).pid = fork();
	if ((d->p[i]).pid < 0)
		return (-1);
		
// execute if process is a child

	if ((d->p[i]).pid == 0)
	{
				
	// redirect std input

		if (i == 0)
		{
			infile_fd = open(d->infile, O_RDONLY);
			if (infile_fd < 0)
			{
				perror("open");
				return -1;
			}
			dup2(infile_fd, STDIN_FILENO);
			close(infile_fd);
		}
		else
			dup2((d->p[i - 1]).fd[0], STDIN_FILENO);
		// close((d->p[i - 1]).fd[0]);
		close((d->p[i - 1]).fd[1]);
	// redirect std output
		
		if(i > d->extra_cmd)
		{
			outfile_fd = open(d->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (outfile_fd < 0)
			{
				perror("open");
				return -1;
			}
			dup2(outfile_fd, STDOUT_FILENO);
			close(outfile_fd);
		}
		else
			dup2((d->p[i]).fd[1], STDOUT_FILENO);
		close((d->p[i]).fd[0]);
		close((d->p[i]).fd[1]);

	// execute command
	
		// ft_printf("\n-> %s", (d->p[i]).cmd);
		execve((d->p[i]).cmd, (d->p[i]).args, NULL);
		perror("execve");	
		exit(EXIT_FAILURE);
		
	}

	return (0);
}
