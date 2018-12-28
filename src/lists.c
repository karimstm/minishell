/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 14:57:32 by amoutik           #+#    #+#             */
/*   Updated: 2018/12/24 15:10:10 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_list(t_command_list  *listptr)
{
	listptr->head = NULL;
	listptr->tail = NULL;
	listptr->node_count = 0;
}

void    push(t_command_list *listptr, char **command)
{
	t_command *newNodePtr = (t_command *)malloc(sizeof(t_command));
	if (newNodePtr == NULL)
		return ;
	newNodePtr->command = command;
	newNodePtr->next = NULL;
	if (listptr->node_count == 0)
	{
		listptr->head = newNodePtr;
		listptr->tail = newNodePtr;
	}
	else
	{
		newNodePtr->next = listptr->head;
		listptr->head = newNodePtr;
	}
	listptr->node_count++;
}
