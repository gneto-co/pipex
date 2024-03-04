/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:29:13 by gabriel           #+#    #+#             */
/*   Updated: 2024/03/04 17:10:53 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

int main(int ac, char *av[]) 
{
	t_data d;

	if (ac != 5)
	{
		ft_printf("Invalid arguments\nExpected:\n./pipex file1 cmd1 cmd2 file2\n");
		return 10;
	}

	// --- put av[] args into args1 and args2 --- //

	d.args1 = ft_split(av[2], ' ');
	d.args2 = ft_split(av[3], ' ');
	d.infile = ft_strdup(av[1]);
	d.outfile = ft_strdup(av[4]);
	

	d.cmd1 = ft_multi_strjoin("/bin/%s",d.args1[0]);
	d.cmd2 = ft_multi_strjoin("/bin/%s",d.args2[0]);
	
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
	
	// --- --- //
	
    if (pipe(d.fd) == -1)
        return 11;

    process1(&d);
    process2(&d);


    close(d.fd[0]);
    close(d.fd[1]);

    waitpid(d.pid1, NULL, 0);
    waitpid(d.pid2, NULL, 0);

	ft_free_array(d.args1);
	ft_free_array(d.args2);
	free(d.cmd1);
	free(d.cmd2);
	free(d.infile);
	free(d.outfile);
    return 0;
}
