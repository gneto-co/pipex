/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:29:13 by gabriel           #+#    #+#             */
/*   Updated: 2024/02/29 16:10:32 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_files/pipex.h"
#include <stdio.h>

int main(int ac, char *av[]) {
	t_data d;

	if (ac != 5)
		return 4;

	// --- put av[] args into args1 and args2 --- //
		
	char	*temp;
	

	temp = ft_multi_strjoin("%s %s", av[2], av[1]);
	d.args1 = ft_split(temp, ' ');
	d.args2 = ft_split(av[3], ' ');
	d.outfile = ft_strdup(av[4]);
	

	d.cmd1 = ft_multi_strjoin("/bin/%s",d.args1[0]);
	d.cmd2 = ft_multi_strjoin("/bin/%s",d.args2[0]);
	
	// ------------------------------ //
	
    if (pipe(d.fd) == -1)
        return 1;

    process1(&d);
	
    process2(&d);


    close(d.fd[0]);
    close(d.fd[1]);

    waitpid(d.pid1, NULL, 0);
    waitpid(d.pid2, NULL, 0);

	ft_free_array(d.args1);
	ft_free_array(d.args2);
	free(temp);
	free(d.cmd1);
	free(d.cmd2);
	free(d.outfile);
    return 0;
}