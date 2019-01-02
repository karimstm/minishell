/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 15:42:35 by amoutik           #+#    #+#             */
/*   Updated: 2019/01/01 16:10:09 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_exists(char *filename)
{
	if (access(filename, F_OK) != -1)
		return (1);
	return (0);
}

char	*get_path(char *command)
{
	char *path;
	char *parsed;

	path = ft_getenv("PATH");
	if (path != NULL)
	{
		path = ft_strdup(path);
		parsed = ft_strtok(path, ":");
		if (command == NULL)
			return (command);
		while (parsed != NULL)
		{
			parsed = ft_strjoin(parsed, "/");
			parsed = ft_strjoin(parsed, command);
			if (is_exists(parsed))
				return (parsed);
			parsed = ft_strtok(NULL, ":");
		}
		free(path);
	}
	return (command);
}

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
		if (command[1])
			ft_putenv(command[1]);
		return (1);
	}
	return (0);
}

int		build_in(char **command)
{
	int i;

	i = 1;
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
	if (build_in1(command))
		return (1);
	return (0);
}
