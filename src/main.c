/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 10:15:13 by amoutik           #+#    #+#             */
/*   Updated: 2019/01/01 10:26:41 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define MAX_LEN 1024

char	*readline()
{
	char buffer[MAX_LEN];
	int ret = 0;
	char *current = (char *)malloc(sizeof(char) * 1);
	
	current[0] = '\0';
	while ((ret = read(0, buffer, 1)))
	{
		buffer[ret] = '\0';
		if (strchr(buffer, '\n'))
			break ;
		current = ft_strjoin(current, buffer);
	}
	return (current);
}

char **get_input(char *input)
{
	char **command = (char **)malloc(sizeof(char *) * MAX_LEN);
	char *parsed;
	int  index = 0;
	int		is_exist_tilda = ft_strchr(input, '~') ? 1 : 0;
	int		is_dollar_exists = ft_strchr(input, '$') ? 1 : 0;

	parsed = ft_strtok(input, " ");
	while (parsed != NULL)
	{
		if (is_exist_tilda && (!ft_strcmp(parsed, "~") || !ft_strcmp(parsed, "~/")))
			parsed = ft_strdup(ft_getenv("HOME"));
		if (is_dollar_exists && parsed[0] == '$')
		{
			parsed = ft_getenv(&parsed[1]);
			parsed = parsed ? ft_strdup(parsed) : "";
		}
		command[index] = parsed;
		index++;
		parsed = ft_strtok(NULL, " ");
	}
	command[index] = NULL;
	if (is_exist_tilda)
		free(parsed);
	return (command);
}

int		ft_execvp(const char *file, char *const argv[])
{
	if (execve(file, argv, g_environ) == -1)
		return (-1);
	return (1);
}

int		launch_exec(char **command)
{
	pid_t child_pid;
	int  stat_loc;

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

void	load_shell()
{
	char **command;
	char *input;

	input = readline();
	if (ft_strcmp(input, "exit") == 0)
		exit(0);
	command = get_input(input);
	if (command[0] && !build_in(command))
	{
		command[0] = get_path(command[0]);
		launch_exec(command);
	}
	free(input);
	free(command);
}

void	handler()
{
	write(1, "\n$> ", 4);
}

int		main()
{
	int size = 0;
	extern char **environ;

	while (environ[size])
		size++;
	g_environ = (char **)malloc(sizeof(char *) * (size + 1));
	ft_memcpy((char *)g_environ, (const char *)environ, sizeof(char *) * size);
	g_environ[size] = NULL;
	signal(SIGINT, handler);
	while (1)
	{
		write(1, "$> ", 3);
		load_shell();
	}
	return (0);
}
