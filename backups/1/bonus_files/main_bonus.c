/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:29:13 by gabriel           #+#    #+#             */
/*   Updated: 2024/03/13 17:32:27 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <stdio.h>

/* void ft_free_data(t_data *d)
{
	ft_free_array(d->p->args);
	free(d->p->cmd);
	free(d->infile);
	free(d->outfile);
} */

int main(int ac, char *av[]) 
{
	t_data d;
	int i;
	char	**temp;

	// need at least 5 arguments
	if (ac < 5)
	{
		ft_printf("Invalid arguments\nExpected:\n./pipex file1 cmd1 cmd2 cm3 ... cmdn file2\n");
		return 10;
	}
	// --- count the amount of commands --- //
	
	d.extra_cmd = ac - 5;
	d.p = malloc((d.extra_cmd + 3) * sizeof(t_process_data));

	// --- put av[2 and 3] args into args1 and args2 --- //
	// --- prepare cmd1 and cmd2 --- //
	
// get process data to first command
	i = 0;
	temp = ft_split(av[2], ' ');
	d.p[0] = (t_process_data){temp, ft_multi_strjoin("/bin/%s",temp[0])};
	// ft_free_array(temp);
	i++;

// get process data to middle commands
	while (i < d.extra_cmd + 1)
	{
		temp = ft_split(av[2 + i], ' ');
		d.p[i] = (t_process_data){temp, ft_multi_strjoin("/bin/%s",temp[0])};
		// ft_free_array(temp);
		i++;
	}
// get process data to last command
	
	temp = ft_split(av[2 + i], ' ');
	d.p[i] = (t_process_data){temp, ft_multi_strjoin("/bin/%s",temp[0])};
	// ft_free_array(temp);

// get files data
	
	d.infile = ft_strdup(av[1]);
	d.outfile = ft_strdup(av[4 + d.extra_cmd]);
	
// print the copy of original command

	
	int j;
	ft_printf("\n< %s ", d.infile);
	i = 0;
	while (i < d.extra_cmd + 2)
	{
		j=0;
		while ((d.p[i]).args[j])
		{
			ft_printf("%s ", (d.p[i]).args[j]);
			j++;
		}
		if (i < d.extra_cmd + 1)
			ft_putstr("| ");
		i ++;
	}
	i = 0;
	ft_printf("> %s ", d.outfile);
	
	// while (i < d.extra_cmd + 2)
	// 	ft_printf("\n-> %s", (d.p[i++]).cmd);

// manage pipe error

	ft_printf("\n\n");
	
// process

	i = 0;
	while (i <= d.extra_cmd + 1)
	{
		process(&d, i);
		i++;
	}

	
	
	
// close fd


// wait all process to end
	i = 0;
	while (i < d.extra_cmd + 2)
	{
		waitpid((d.p[i]).pid, NULL, 0);
		ft_printf("\n-> %d", i);
		i++;
	}

	/* 

	// --- free() all stuff --- //

	ft_free_array(d.args1);
	ft_free_array(d.args2);
	free(d.cmd1);
	free(d.cmd2);
	free(d.infile);
	free(d.outfile);
	// free(d.pid_n);
	// free(d.args_n);
	// free(d.cmd_n);
    return 0; */
}
