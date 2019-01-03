/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 15:42:35 by amoutik           #+#    #+#             */
/*   Updated: 2019/01/03 17:01:12 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_exists(char *filename)
{
	if (access(filename, F_OK) != -1)
		return (1);
	return (0);
}

int		is_permitted(char *filename)
{
	if (access(filename, X_OK) != -1)
		return (1);
	return (0);
}

char	*get_path(char *command)
{
	char *path;
	char *parsed;
	char *tmp;

	path = ft_getenv("PATH");
	if (path != NULL)
	{
		path = ft_strdup(path);
		parsed = ft_strtok(path, ":");
		if (command == NULL)
			return (command);
		while (parsed != NULL)
		{
			tmp = ft_strjoin(parsed, "/");
			parsed = ft_strjoin(tmp, command);
			free(tmp);
			if (is_exists(parsed) && is_permitted(parsed))
			{
				tmp = ft_strdup(parsed);
				free(parsed);
				free(path);
				return (tmp);
			}
			free(parsed);
			parsed = ft_strtok(NULL, ":");
		}
		free(path);
	}
	return (ft_strdup(command));
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
		if (command[1] && ft_strchr(command[1], '='))
			ft_putenv(command[1]);
		else if (command[1] && command[2])
			ft_setenv(command[1], command[2], 1);
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
	if (ft_strcmp(command[0], "exit") == 0)
		exit(0);
	return (0);
}
