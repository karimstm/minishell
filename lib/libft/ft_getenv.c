/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 12:58:43 by amoutik           #+#    #+#             */
/*   Updated: 2018/12/24 12:59:16 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_findenv(const char *name, int *offset)
{
	extern char **environ;
	int len, i;
	const char *np;
	char **p, *cp;
	if (name == NULL || environ == NULL)
		return (NULL);
	np = name;
	while (*np && *np != '=')
		++np;
	len = np - name;
	p = environ;
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
			*offset = p - environ;
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
