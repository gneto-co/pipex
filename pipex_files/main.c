/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:29:13 by gabriel           #+#    #+#             */
/*   Updated: 2024/03/21 12:28:53 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

void	ft_free_data(t_data *d)
{
	ft_free_array(d->args1);
	ft_free_array(d->args2);
	free(d->cmd1);
	free(d->cmd2);
	free(d->infile);
	free(d->outfile);
}

int	main(int ac, char *av[])
{
	t_data	d;

	if (ac != 5)
	{
		ft_printf("Invalid arguments\nExpected:\n"
			"./pipex file1 cmd1 cmd2 file2\n");
		return (10);
	}
	d.args1 = ft_split(av[2], ' ');
	d.args2 = ft_split(av[3], ' ');
	d.infile = ft_strdup(av[1]);
	d.outfile = ft_strdup(av[4]);
	d.cmd1 = ft_multi_strjoin("/bin/%s", d.args1[0]);
	d.cmd2 = ft_multi_strjoin("/bin/%s", d.args2[0]);
	if (pipe(d.fd) == -1)
		return (11);
	process1(&d);
	process2(&d);
	close(d.fd[0]);
	close(d.fd[1]);
	waitpid(d.pid1, NULL, 0);
	waitpid(d.pid2, NULL, 0);
	ft_free_data(&d);
	return (0);
}
