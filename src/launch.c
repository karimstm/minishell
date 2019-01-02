/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/02 10:46:15 by amoutik           #+#    #+#             */
/*   Updated: 2019/01/02 10:51:18 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_execvp(const char *file, char *const argv[])
{
	if (execve(file, argv, g_environ) == -1)
		return (-1);
	return (1);
}

int			launch_exec(char **command)
{
	pid_t	child_pid;
	int		stat_loc;

	child_pid = fork();
	if (child_pid == 0)
	{
		if (ft_execvp(command[0], command) == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(command[0], 2);
			ft_putstr_fd(" :command not found\n", 2);
			exit(EXIT_FAILURE);
		}
	}
	else
		waitpid(child_pid, &stat_loc, 0);
	return (1);
}

void		get_commands(char *input, t_command_list *cmd_list)
{
	char *parsed;
	char *commands;

	init_list(cmd_list);
	commands = ft_strdup(input);
	parsed = ft_strtok(commands, ";");
	while (parsed != NULL)
	{
		push(cmd_list, ft_strdup(parsed));
		parsed = ft_strtok(NULL, ";");
	}
}

void		load_shell(void)
{
	char			*input;
	t_command_list	cmd_list;

	input = readline();
	if (ft_strcmp(input, "exit") == 0)
		exit(0);
	get_commands(input, &cmd_list);
	print_commands(&cmd_list);
	free(input);
}
