/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 15:42:35 by amoutik           #+#    #+#             */
/*   Updated: 2019/01/05 13:24:41 by amoutik          ###   ########.fr       */
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

char	*token_path(char *command, char *parsed, char *path, int *permetted)
{
	char *tmp;

	while (parsed != NULL)
	{
		tmp = ft_strjoin(parsed, "/");
		parsed = ft_strjoin(tmp, command);
		free(tmp);
		if (is_exists(parsed))
		{
			if (!is_permitted(parsed))
			{
				*permetted = 0;
				continue;
			}
			else if (is_permitted(parsed))
				*permetted = 1;
			tmp = ft_strdup(parsed);
			free(parsed);
			free(path);
			return (tmp);
		}
		free(parsed);
		parsed = ft_strtok(NULL, ":");
	}
	return (NULL);
}

char	*get_path(char *command, int *permetted)
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
		tmp = token_path(command, parsed, path, permetted);
		if (tmp)
			return (tmp);
		free(path);
	}
	return (ft_strdup(command));
}
