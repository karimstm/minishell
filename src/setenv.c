/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 11:15:37 by amoutik           #+#    #+#             */
/*   Updated: 2018/12/29 14:00:58 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
int		ft_putenv(const char *env)
{
	//something goes here
}
*/

int		ft_setenv(const char *name, const char *value, int overwrite)
{
	char *env;
	int	len;

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
	return (putenv(env) != 0 ? -1 : 0);
}
