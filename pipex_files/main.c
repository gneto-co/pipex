/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:29:13 by gabriel           #+#    #+#             */
/*   Updated: 2024/04/09 10:29:08 by gneto-co         ###   ########.fr       */
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

char	*ft_find_cmd_path(char **env, char *cmd)
{
	int		i;
	char	*r;
	char	*path_str;
	char	**path_array;
	char	*temp;

	path_str = ft_n_find_on_array(env, "PATH", 4);
	path_array = ft_split(path_str, ':');
	temp = path_array[0];
	path_array[0] = ft_strdup(path_array[0] + 5);
	free(temp);
	i = 0;
	r = NULL;
	while (path_array[i] && !r)
	{
		temp = ft_multi_strjoin("%s/%s", path_array[i], cmd);
		if (access(temp, F_OK) != -1)
			r = ft_strdup(temp);
		free(temp);
		i++;
	}
	ft_free_array(path_array);
	return (r);
}

static int	failure_check(t_data *d)
{
	if (!d->cmd1 || !d->cmd2)
	{
		ft_free_data(d);
		ft_printf("Invalid command");
		return (1);
	}
	if (access(d->infile, F_OK) < 0)
	{
		ft_free_data(d);
		ft_printf("Invalid infile");
		return (1);
	}
	if (pipe(d->fd) == -1)
	{
		ft_free_data(d);
		ft_printf("Pipe error");
		return (1);
	}
	return (0);
}

int	main(int ac, char *av[], char **env)
{
	t_data	d;

	if (ac != 5)
	{
		ft_printf("Invalid arguments\nExpected:\n"
			"./pipex infile cmd1 cmd2 outfile\n");
		return (1);
	}
	d.args1 = ft_split(av[2], ' ');
	d.args2 = ft_split(av[3], ' ');
	d.infile = ft_strdup(av[1]);
	d.outfile = ft_strdup(av[4]);
	d.cmd1 = ft_find_cmd_path(env, d.args1[0]);
	d.cmd2 = ft_find_cmd_path(env, d.args2[0]);
	if (failure_check(&d))
		return (1);
	process1(&d);
	process2(&d);
	close(d.fd[0]);
	close(d.fd[1]);
	waitpid(d.pid1, NULL, 0);
	waitpid(d.pid2, NULL, 0);
	ft_free_data(&d);
	return (0);
}
