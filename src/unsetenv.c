/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 09:53:24 by amoutik           #+#    #+#             */
/*   Updated: 2019/01/01 10:55:02 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_unsetenv(const char *name)
{
	char **p;
	int offset;
	while (ft_findenv(name, &offset))
	{
		p = &g_environ[offset];
		while (1)
		{
			if (!(*p = *(p + 1)))
				break;
			++p;
		}
	}
	return 0;

}
