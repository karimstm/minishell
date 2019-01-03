/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 11:15:37 by amoutik           #+#    #+#             */
/*   Updated: 2019/01/03 15:38:58 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		set_new_env(char *entry, char **p)
{
	unsigned	size;
	char		**new_environ;

	size = p - g_environ;
	new_environ = (char **)malloc(sizeof(char *) * (size + 2));
	if (new_environ == (char **)NULL)
		return (-1);
	ft_memcpy((char *)new_environ,
			(const char *)g_environ, size * sizeof(char *));
	new_environ[size] = entry;
	new_environ[size + 1] = NULL;
	free(g_environ);
	g_environ = new_environ;
	return (0);
}

int		ft_putenv(char *entry)
{
	unsigned	length;
	char		*tmp;
	char		**p;

	tmp = ft_strchr(entry, '=');
	if (tmp == NULL)
		return (-1);
	length = (unsigned)(tmp - entry + 1);
	p = g_environ;
	while (*p != NULL)
	{
		if (ft_strncmp(entry, *p, length) == 0)
		{
			*p = entry;
			return (0);
		}
		++p;
	}
	return (set_new_env(entry, p));
}

int		ft_setenv(const char *name, const char *value, int overwrite)
{
	char	*env;
	int		len;

	if (name == NULL || name[0] == '\0' || value == NULL)
		return (-1);
	if (ft_getenv(name) != NULL && overwrite == 0)
		return (0);
	len = ft_strlen(name) + ft_strlen(value) + 2;
	if (!(env = (char *)malloc(sizeof(char) * len)))
		return (-1);
	ft_strcat(env, name);
	ft_strcat(env, "=");
	ft_strcat(env, value);
	return (ft_putenv(env) != 0 ? -1 : 0);
}
