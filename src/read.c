/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/02 10:37:59 by amoutik           #+#    #+#             */
/*   Updated: 2019/01/07 08:02:33 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*readline(void)
{
	char	buffer[MAX_LEN];
	int		ret;
	char	*current;
	char	*tmp;

	ret = 0;
	if (!(current = (char *)malloc(sizeof(char))))
		return (NULL);
	current[0] = '\0';
	while ((ret = read(0, buffer, 1)))
	{
		buffer[ret] = '\0';
		if (ft_strchr(buffer, '\n'))
			break ;
		tmp = current;
		current = ft_strjoin(current, buffer);
		free(tmp);
	}
	return (current);
}

char		*manage_tilda(char *parsed, int is_exist_tilda)
{
	char *path;

	path = ft_getenv("HOME");
	if (is_exist_tilda == 1 && !ft_strcmp(parsed, "~"))
		return (parsed = path);
	if (is_exist_tilda == 1 && parsed[1] == '/' && path)
		parsed = ft_strjoin(path, &parsed[1]);
	return (parsed);
}

char		*manage_dollar(char *parsed, int is_dollar_exists)
{
	if (is_dollar_exists == 1 && parsed[0] == '$')
		parsed = ft_getenv(&parsed[1]);
	return (parsed);
}

int			isempty(char *str)
{
	if (str == NULL)
		return (1);
	return (0);
}

char		**get_input(char *input)
{
	char	**command;
	char	*parsed;
	int		index;
	int		is_dollar_exists;
	int		is_exist_tilda;

	is_exist_tilda = ft_strchr(input, '~') ? 1 : 0;
	is_dollar_exists = ft_strchr(input, '$') ? 1 : 0;
	index = 0;
	parsed = ft_strtok(input, " \t\"");
	if (!(command = (char **)malloc(sizeof(char *) * MAX_LEN)))
		return (NULL);
	while (parsed != NULL)
	{
		parsed = manage_tilda(parsed, is_exist_tilda);
		parsed = manage_dollar(parsed, is_dollar_exists);
		command[index] = parsed;
		parsed = ft_strtok(NULL, " \t\"");
		index++;
	}
	command[index] = NULL;
	return (command);
}
