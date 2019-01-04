/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 10:15:13 by amoutik           #+#    #+#             */
/*   Updated: 2019/01/04 19:15:24 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		free_list_of_commands(t_command_list *cmd)
{
	t_command *current;
	t_command *tmp;

	if (cmd->node_count)
	{
		current = cmd->head;
		while (current)
		{
			tmp = current->next;
			free(current->command);
			free(current);
			current = tmp;
		}
		free(tmp);
	}
	init_list(cmd);
}

void		free_command(char **command)
{
	int i;

	i = 0;
	while (command[i])
	{
		free(command[i]);
		i++;
	}
	free(command);
}

void		error(char *message, char *command)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd("\n", 2);
}

void		print_commands(t_command_list *cmd)
{
	t_command	*current;
	char		**command;
	int			is_permetted;

	is_permetted = 1;
	if (cmd->node_count)
	{
		current = cmd->head;
		while (current)
		{
			command = get_input(current->command);
			if (command[0] && !build_in(command))
			{
				g_set_signal = 1;
				command[0] = get_path(command[0], &is_permetted);
				is_permetted == 1 ? launch_exec(command) :
					error("permission denied: ", command[0]);
				command[0] ? free(command[0]) : 0;
			}
			free(command);
			current = current->next;
		}
		free_list_of_commands(cmd);
	}
}

void		handler(int signal)
{
	signal = 0;
	if (g_set_signal == 0)
		write(1, "\n$> ", 4);
	if (g_set_signal == 1)
		write(1, "\n", 1);
}

int			main(void)
{
	int			size;
	extern char	**environ;

	size = 0;
	while (environ[size])
		size++;
	if (!(g_environ = (char **)malloc(sizeof(char *) * (size + 1))))
		;
	ft_memcpy((char *)g_environ, (const char *)environ, sizeof(char *) * size);
	g_environ[size] = NULL;
	signal(SIGINT, &handler);
	while (1)
	{
		write(1, "$> ", 3);
		load_shell();
		g_set_signal = 0;
	}
	free(g_environ);
	return (0);
}
