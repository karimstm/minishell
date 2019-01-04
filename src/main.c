/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 10:15:13 by amoutik           #+#    #+#             */
/*   Updated: 2019/01/03 16:02:31 by amoutik          ###   ########.fr       */
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

void		print_commands(t_command_list *cmd)
{
	t_command	*current;
	char		**command;

	if (cmd->node_count)
	{
		current = cmd->head;
		while (current)
		{
			command = get_input(current->command);
			if (command[0] && !build_in(command))
			{
				command[0] = get_path(command[0]);
				launch_exec(command);
				if (command[0])
					free(command[0]);
			}
			free(command);
			current = current->next;
		}
		free_list_of_commands(cmd);
	}
}

void		handler()
{
	write(1, "\n$> ", 4);
}

int			main(void)
{
	int			size;
	extern char	**environ;

	size = 0;
	while (environ[size])
		size++;
	if (!(g_environ = (char **)malloc(sizeof(char *) * (size + 1))))
	{}
	ft_memcpy((char *)g_environ, (const char *)environ, sizeof(char *) * size);
	g_environ[size] = NULL;
	signal(SIGINT, &handler);
	while (1)
	{
		write(1, "$> ", 3);
		load_shell();
	}
	free(g_environ);
	return (0);
}
