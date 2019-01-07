/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 13:23:57 by amoutik           #+#    #+#             */
/*   Updated: 2019/01/05 17:28:08 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		build_in1(char **command)
{
	int i;

	i = 0;
	if (!ft_strcmp("echo", command[0]))
	{
		echo(command);
		return (1);
	}
	if (!ft_strcmp("unsetenv", command[0]))
	{
		while (command[i])
			ft_unsetenv(command[i++]);
		return (1);
	}
	if (!ft_strcmp("setenv", command[0]))
	{
		if (command[1] && ft_strchr(command[1], '='))
			ft_putenv(ft_strdup(command[1]));
		else if (command[1] && command[2])
			ft_setenv(ft_strdup(command[1]), ft_strdup(command[2]), 1);
		return (1);
	}
	return (0);
}

int		build_in(char **command)
{
	if (ft_strcmp("env", command[0]) == 0)
	{
		print_env();
		return (1);
	}
	if (ft_strcmp("cd", command[0]) == 0)
	{
		char_dir(command);
		return (1);
	}
	if (!ft_strcmp("which", command[0]))
	{
		whereis(command);
		return (1);
	}
	if (build_in1(command))
		return (1);
	if (ft_strcmp(command[0], "exit") == 0)
		exit(0);
	return (0);
}

int		built_in(char *command)
{
	if (!ft_strcmp("env", command) || !ft_strcmp("unsetenv", command))
		return (1);
	if (!ft_strcmp("which", command) || !ft_strcmp("exit", command))
		return (1);
	if (!ft_strcmp("setenv", command) || !ft_strcmp("cd", command))
		return (1);
	if (!ft_strcmp("echo", command))
		return (1);
	return (0);
}

void	whereis(char **command)
{
	int i;
	int perm;

	i = 1;
	perm = 0;
	while (command[i])
	{
		if (built_in(command[i]))
		{
			ft_putstr(command[i]);
			ft_putstr(": minishell built-in command");
		}
		else
			ft_putstr(get_path(command[i], &perm));
		ft_putchar('\n');
		i++;
	}
}
