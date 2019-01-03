/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 18:06:34 by amoutik           #+#    #+#             */
/*   Updated: 2019/01/03 16:53:04 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_env(char *oldpath, char *newpath)
{
	if (oldpath == NULL)
		oldpath = newpath;
	ft_setenv("OLDPWD", oldpath, 1);
}

int		old_path(char *path[], char *currentpath, char *oldpath)
{
	if (path[1][0] == '-')
	{
		if (ft_strlen(path[1]))
		{
			if (chdir(oldpath) != -1)
			{
				change_env(currentpath, oldpath);
				ft_setenv("PWD", oldpath, 1);
			}
			return (1);
		}
	}
	return (0);
}

void	is_accessible(char *path)
{
	struct stat buf;

	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	if (lstat(path, &buf) == -1)
	{
		ft_putstr_fd(": No such file or directory\n", 2);
		return ;
	}
	if (!M_ISDIR(buf.st_mode))
	{
		ft_putstr_fd(" Not a directory\n", 2);
		return ;
	}
	if (access(path, R_OK) == -1)
	{
		ft_putstr_fd(" Permission denied\n", 2);
		return ;
	}
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
		is_accessible(path[1]);
	else
		change_env(currentpath, path[1]);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_setenv("PWD", cwd, 1);
}
