/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:29:13 by gabriel           #+#    #+#             */
/*   Updated: 2024/03/07 10:48:57 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <stdio.h>

int main(int ac, char *av[]) 
{
	t_data d;
	int i;

	// need at least 5 arguments
	if (ac < 5)
	{
		ft_printf("Invalid arguments\nExpected:\n./pipex file1 cmd1 cmd2 cm3 ... cmdn file2\n");
		return 10;
	}

	// --- put av[2 and 3] args into args1 and args2 --- //
	// --- prepare cmd1 and cmd2 --- //

	d.args1 = ft_split(av[2], ' ');
	d.args2 = ft_split(av[3], ' ');
	d.cmd1 = ft_multi_strjoin("/bin/%s",d.args1[0]);
	d.cmd2 = ft_multi_strjoin("/bin/%s",d.args2[0]);

	// --- initialize in and out files --- //
	
	d.infile = ft_strdup(av[1]);
	d.outfile = ft_strdup(av[4]);

	// --- count the amount of commands --- //
	
	d.extra_cmd = ac - 5;

	// --- malloc all _n variables --- //
	
	d.pid_n = malloc(sizeof(int) * d.extra_cmd);
	d.args_n = malloc(sizeof(char **) * d.extra_cmd);
	d.cmd_n = malloc(sizeof(char *) * d.extra_cmd);
	
	// --- put commands into args_n[] and cmd_n[] --- //
	
	i = 0;
	while (i < d.extra_cmd)
	{
		d.args_n[i] = ft_split(av[4 + i], ' ');
		d.cmd_n[i] = ft_multi_strjoin("/bin/%s",d.args_n[i][0]);
		i++;
	}
	
	
	// --- print args --- //

	// int i;
	// i=0;
	// ft_printf("< %s ", d.infile);
	// while (d.args1[i])
	// {
	// 	ft_printf("%s ", d.args1[i]);
	// 	i ++;
	// }
	// ft_putstr("| ");
	// i=0;
	// while (d.args2[i])
	// {
	// 	ft_printf("%s ", d.args2[i]);
	// 	i ++;
	// }
	// ft_printf("> %s\n\n", d.outfile);
	
	
	// --- manage pipe error --- //
    if (pipe(d.fd) == -1)
        return 11;
		
	
	// --- process 1 --- //
    process1(&d);
	// --- process n --- //
	d.i = 0;
	while (d.i < d.extra_cmd)
	{
		process_n(&d);
		d.i++;
	}
	// --- process 2 --- //
    process2(&d);
	
	
	// --- close fd --- //
    close(d.fd[0]);
    close(d.fd[1]);


	// --- wait all process to end --- //
    waitpid(d.pid1, NULL, 0);
	i = 0;
	while (i < d.extra_cmd)
	{
		waitpid(d.pid_n[i], NULL, 0);
		i++;
	}
    waitpid(d.pid2, NULL, 0);


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
    return 0;
}
