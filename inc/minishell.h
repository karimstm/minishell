/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 10:19:40 by amoutik           #+#    #+#             */
/*   Updated: 2018/12/24 15:57:00 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include "libft.h"

typedef struct	s_command
{
	char				**command;
	struct	s_command	*next;
}				t_command;

typedef struct	s_command_s
{
	struct	s_command	*head;
	struct	s_command	*tail;
	int					node_count;
}				t_command_list;

void    push(t_command_list *listptr, char **data);
void	init_list(t_command_list *listPtr);
int		is_exists(char *filename);
char	*get_path(char *command);

#endif
