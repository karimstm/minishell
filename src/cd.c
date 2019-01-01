/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 18:06:34 by amoutik           #+#    #+#             */
/*   Updated: 2018/12/31 15:51:42 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	change_env(char *oldpath, char *newpath)
{
	if (newpath[0] != '/')
		newpath = ft_strjoin(ft_strjoin(oldpath, "/"), newpath);
	/* Do not forget the implement the two '..' into your code */
	ft_setenv("OLDPWD", oldpath, 1);
	ft_setenv("PWD", newpath, 1);
}

void	char_dir(char *path[])
{
	char *homepath = ft_getenv("HOME");
	char *currentpath = ft_getenv("PWD");
	char *oldpath = ft_getenv("OLDPWD");
	char cwd[PATH_MAX];

	if (path[1] == NULL)
	{
		if (chdir(homepath) != -1)
			change_env(currentpath, homepath);
		return ;
	}
	if (path[1][0] == '-')
	{
		if (ft_strlen(path[1]))
		{
			if (chdir(oldpath) != -1)
				change_env(currentpath, oldpath);
			return ;
		}
	}
	if (chdir(path[1]) == -1)
	{
		ft_putstr_fd(path[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else
		change_env(currentpath, path[1]);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_setenv("PWD", cwd, 1);
}
