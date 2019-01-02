/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 12:58:43 by amoutik           #+#    #+#             */
/*   Updated: 2019/01/02 11:01:47 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			check_name(const char *name, const char *np, int *len)
{
	if (name == NULL || g_environ == NULL)
		return (0);
	np = name;
	while (*np && *np != '=')
		++np;
	*len = np - name;
	return (1);
}

char		*return_env(char *cp, char **p, int *offset)
{
	*offset = p - g_environ;
	return (cp);
}

char		*ft_findenv(const char *name, int *offset)
{
	int			len;
	int			i;
	const char	*np;
	char		**p;
	char		*cp;

	if (!check_name(name, np, &len))
		return (NULL);
	p = g_environ;
	while ((cp = *p) != NULL)
	{
		np = name;
		i = len;
		while (i && *cp)
		{
			if (*cp++ != *np++)
				break ;
			i--;
		}
		if (i == 0 && *cp++ == '=')
			return (return_env(cp, p, offset));
		++p;
	}
	return (NULL);
}

char		*ft_getenv(const char *name)
{
	int offset;

	return (ft_findenv(name, &offset));
}
