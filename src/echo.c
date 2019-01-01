/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 10:59:13 by amoutik           #+#    #+#             */
/*   Updated: 2018/12/31 14:26:24 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(char **command)
{
	int i;
	int newline;

	i = 1;
	newline = 0;
	if (command[i] && command[i][0] == '-' && command[i][1] == 'n')
	{
		newline = 1;
		i++;
	}
	while (command[i])
	{
		printf("%s%c", command[i], command[i + 1] ? ' ': '\0');
		++i;
	}
	if (!newline)
		printf("\n");
}
