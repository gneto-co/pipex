/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 19:01:08 by gabriel           #+#    #+#             */
/*   Updated: 2024/03/07 10:48:07 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/* *********************************** */
/*                                     */
/*             PIPEX HEADER              */
/*                                     */
/* *********************************** */

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

# define INT_MAX 2147483647
# define INT_MIN -2147483648

typedef struct s_data
{
	int		fd[2];
	int		extra_cmd;
	int		i;
	// 1
	int		pid1;
	char	**args1;
	char	*cmd1;
	// n
	int		*pid_n;
	char	***args_n;
	char	**cmd_n;
	// 2
	int		pid2;
	char	**args2;
	char	*cmd2;
	// files
	char	*infile;
	char	*outfile;
}			t_data;

int			process1(t_data *d);
int			process2(t_data *d);
int			process_n(t_data *d);

/* *********************************** */
/*                                     */
/*                 END                 */
/*                                     */
/* *********************************** */

#endif