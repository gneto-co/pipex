/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:29:13 by gabriel           #+#    #+#             */
/*   Updated: 2024/02/29 15:46:54 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_files/pipex.h"
#include <stdio.h>

int main(int ac, char *av[]) {
    (void)ac;
    (void)av;

	// if (ac != 5)
	// 	return 4;

	// --- put av[] args into args1 and args2 --- //
		
	char	*temp;
	char	**args1;
	char	**args2;
	char	*cmd1;
	char	*cmd2;

	temp = ft_multi_strjoin("%s %s", av[2], av[1]);
	args1 = ft_split(temp, ' ');
	args2 = ft_split(av[3], ' ');
	free(temp);
	

	cmd1 = ft_multi_strjoin("/bin/%s",args1[0]);
	cmd2 = ft_multi_strjoin("/bin/%s",args2[0]);
	// char *args1[] = {"grep", "int", "main.c", NULL};
	// char *args2[] = {"grep", ";", NULL};

	// char *cmd1 = "/bin/grep";
	// char *cmd2 = "/bin/grep";
	
	// ------------------------------ //
	
    int fd[2];
    if (pipe(fd) == -1)
        return 1;

    int pid1 = fork();
    if (pid1 < 0)
        return 2;

    if (pid1 == 0) {
        // child process 1
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        
        execve(cmd1, args1, NULL);
        
        // Se execve() retornar, algo deu errado
        perror("execve");
        exit(EXIT_FAILURE);
    }

    int pid2 = fork();
    if (pid2 < 0)
        return 3;

    if (pid2 == 0) {
        // child process 2
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);
        
		int outfile_fd = open("outfile", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (outfile_fd == -1) {
            perror("open");
            return 5;
        }
        dup2(outfile_fd, STDOUT_FILENO);
		
        execve(cmd2, args2, NULL);
        
        // Se execve() retornar, algo deu errado
        perror("execve");
        exit(EXIT_FAILURE);
    }

    close(fd[0]);
    close(fd[1]);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}