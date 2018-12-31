/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 15:42:35 by amoutik           #+#    #+#             */
/*   Updated: 2018/12/29 10:41:01 by amoutik          ###   ########.fr       */
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

	path = ft_strdup(ft_getenv("PATH"));
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
	return (command);
}

int		build_in(char **command)
{
	if (ft_strcmp("env", command[0]) == 0)
	{
		print_env();
		return (1);
	}
	if (ft_strcmp("cd" , command[0]) == 0)
	{
		char_dir(command);
		return (1);
	}
	return (0);
}
