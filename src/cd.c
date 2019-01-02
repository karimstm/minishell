/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 18:06:34 by amoutik           #+#    #+#             */
/*   Updated: 2019/01/02 10:20:16 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_env(char *oldpath, char *newpath)
{
	if (oldpath == NULL)
		oldpath = newpath;
	ft_setenv("OLDPWD", oldpath, 1);
	ft_setenv("PWD", newpath, 1);
}

int		old_path(char *path[], char *currentpath, char *oldpath)
{
	if (path[1][0] == '-')
	{
		if (ft_strlen(path[1]))
		{
			if (chdir(oldpath) != -1)
				change_env(currentpath, oldpath);
			return (1);
		}
	}
	return (0);
}

void	char_dir(char *path[])
{
	char *homepath;
	char *currentpath;
	char *oldpath;
	char cwd[PATH_MAX];

	homepath = ft_getenv("HOME");
	currentpath = ft_getenv("PWD");
	oldpath = ft_getenv("OLDPWD");
	if (path[1] == NULL)
	{
		if (chdir(homepath) != -1)
			change_env(currentpath, homepath);
		return ;
	}
	if (old_path(path, currentpath, oldpath))
		return ;
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
