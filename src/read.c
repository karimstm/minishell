/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/02 10:37:59 by amoutik           #+#    #+#             */
/*   Updated: 2019/01/02 10:39:49 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*readline(void)
{
	char	buffer[MAX_LEN];
	int		ret;
	char	*current;

	ret = 0;
	if (!(current = (char *)malloc(sizeof(char))))
		return (NULL);
	current[0] = '\0';
	while ((ret = read(0, buffer, 1)))
	{
		buffer[ret] = '\0';
		if (ft_strchr(buffer, '\n'))
			break ;
		current = ft_strjoin(current, buffer);
	}
	return (current);
}

char		*manage_tilda(char *parsed, int is_exist_tilda)
{
	if (is_exist_tilda && (!ft_strcmp(parsed, "~")
				|| !ft_strcmp(parsed, "~/")))
		parsed = ft_strdup(ft_getenv("HOME"));
	return (parsed);
}

char		*manage_dollar(char *parsed, int is_dollar_exists)
{
	if (is_dollar_exists && parsed[0] == '$')
	{
		parsed = ft_getenv(&parsed[1]);
		parsed = parsed ? ft_strdup(parsed) : ft_strdup("");
	}
	return (parsed);
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
	parsed = ft_strtok(input, " ");
	if (!(command = (char **)malloc(sizeof(char *) * MAX_LEN)))
		return (NULL);
	while (parsed != NULL)
	{
		parsed = manage_tilda(parsed, is_exist_tilda);
		parsed = manage_dollar(parsed, is_dollar_exists);
		command[index] = parsed;
		parsed = ft_strtok(NULL, " ");
		if (parsed)
			parsed = ft_strdup(parsed);
		index++;
	}
	command[index] = NULL;
	return (command);
}
