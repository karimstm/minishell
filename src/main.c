/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 10:15:13 by amoutik           #+#    #+#             */
/*   Updated: 2018/12/29 10:36:28 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define MAX_LEN 1024

char	*readline()
{
	char buffer[MAX_LEN];
	int ret = 0;
	char *current = (char *)malloc(sizeof(char) * 1);

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
	char *separator = " ";
	char *parsed;
	int  index = 0;

	parsed = ft_strtok(input, separator);
	while (parsed != NULL)
	{
		command[index] = parsed;
		index++;
		parsed = ft_strtok(NULL, separator);
	}
	command[index] = NULL;
	return (command);
}

int		ft_execvp(const char *file, char *const argv[])
{
	extern char **environ;
	if (execve(file, argv, environ) == -1)
		return (-1);
	return (1);
}

char	*read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;
	getline(&line, &bufsize, stdin);
	line[ft_strlen(line) - 1] = '\0';
	return line;
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

	//input = readline();
	input = read_line();
	if (ft_strcmp(input, "exit") == 0)
		exit(0);
	command = get_input(input);
	if (!build_in(command))
	{
		command[0] = get_path(command[0]);
		launch_exec(command);
	}
	free(input);
	free(command);
}

int		main()
{
	while (1)
	{
		printf("$> ");
		//fflush(stdout);
		load_shell();
	}
	return (0);
}
