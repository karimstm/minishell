/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 10:59:13 by amoutik           #+#    #+#             */
/*   Updated: 2019/01/02 11:04:31 by amoutik          ###   ########.fr       */
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
		ft_putstr(command[i]);
		ft_putchar(command[i + 1] ? ' ' : '\0');
		++i;
	}
	if (!newline)
		ft_putchar('\n');
}
