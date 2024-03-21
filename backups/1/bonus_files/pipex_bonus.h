/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 19:01:08 by gabriel           #+#    #+#             */
/*   Updated: 2024/03/13 15:43:39 by gneto-co         ###   ########.fr       */
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

typedef struct s_process_data
{
	char			**args;
	char			*cmd;
	int				pid;
	int				fd[2];
}					t_process_data;

typedef struct s_data
{
	t_process_data	*p;
	int				extra_cmd;
	int				i;
	char			*infile;
	char			*outfile;
}					t_data;

int					process(t_data *d, int i);
void				ft_free_data(t_data *d);

/* *********************************** */
/*                                     */
/*                 END                 */
/*                                     */
/* *********************************** */

#endif