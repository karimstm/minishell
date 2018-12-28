/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 15:42:35 by amoutik           #+#    #+#             */
/*   Updated: 2018/12/24 17:36:27 by amoutik          ###   ########.fr       */
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
	char **files;
	char *parsed;
	int i;

	if ((files = (char **)malloc(sizeof(char *) * 100)) == NULL)
		return (NULL);
	path = ft_getenv("PATH");
	i = 0;
	parsed = ft_strtok(path, ":");
	while (parsed != NULL)
	{
		files[i] = ft_strjoin(parsed, "/");
		files[i] = ft_strjoin(files[i], command);
		if (is_exists(files[i]))
		{
			command = ft_strdup(files[i]);
			break ;
		}
		parsed = ft_strtok(NULL, ":");
		i++;
	}
	free(files);
	return (command);
}
