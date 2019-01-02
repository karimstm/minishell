/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 14:57:32 by amoutik           #+#    #+#             */
/*   Updated: 2019/01/01 16:34:46 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_list(t_command_list *listptr)
{
	listptr->head = NULL;
	listptr->tail = NULL;
	listptr->node_count = 0;
}

void	push(t_command_list *listptr, char *command)
{
	t_command *new_node_ptr;

	new_node_ptr = (t_command *)malloc(sizeof(t_command));
	if (new_node_ptr == NULL)
		return ;
	new_node_ptr->command = command;
	new_node_ptr->next = NULL;
	if (listptr->node_count == 0)
	{
		listptr->head = new_node_ptr;
		listptr->tail = new_node_ptr;
	}
	else
	{
		listptr->tail->next = new_node_ptr;
		listptr->tail = new_node_ptr;
	}
	listptr->node_count++;
}
