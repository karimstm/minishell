/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 12:58:43 by amoutik           #+#    #+#             */
/*   Updated: 2018/12/31 15:20:10 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_findenv(const char *name, int *offset)
{
	int len, i;
	const char *np;
	char **p, *cp;
	if (name == NULL || g_environ == NULL)
		return (NULL);
	np = name;
	while (*np && *np != '=')
		++np;
	len = np - name;
	p = g_environ;
	while ((cp = *p) != NULL)
	{
		np = name;
		i = len;
		while (i && *cp)
		{
			if (*cp++ != *np++)
				break;
			i--;
		}
		if (i == 0 && *cp++ == '=') {
			*offset = p - g_environ;
			return (cp);
		}
		++p;
	}
	return (NULL);
}

char *ft_getenv(const char *name)
{
	int offset;
	return (ft_findenv(name, &offset));
}
