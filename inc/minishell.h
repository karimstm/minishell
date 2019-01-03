/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 10:19:40 by amoutik           #+#    #+#             */
/*   Updated: 2019/01/02 14:40:14 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <signal.h>
# include <unistd.h>
# include <sys/stat.h>
# include "libft.h"

# define MAX_LEN 1024
# define M_ISDIR(m)	((m & 0170000) == 0040000)

typedef struct			s_command
{
	char				*command;
	struct s_command	*next;
}						t_command;

typedef struct			s_command_s
{
	struct s_command	*head;
	struct s_command	*tail;
	int					node_count;
}						t_command_list;

char					**g_environ;

void					push(t_command_list *listptr, char *data);
void					init_list(t_command_list *list_ptr);
int						is_exists(char *filename);
char					*get_path(char *command);
void					char_dir(char *path[]);
int						build_in(char **command);
int						ft_setenv(const char *name,
		const char *value, int overwrite);
char					*ft_getenv(const char *name);
char					*ft_findenv(const char *name, int *offset);
void					echo(char **command);
int						ft_unsetenv(const char *name);
int						ft_putenv(char *entry);
void					print_env();
char					**get_input(char *input);
char					*manage_dollar(char *parsed, int is_dollar_exists);
char					*manage_tilda(char *parsed, int is_exist_tilda);
char					*readline(void);
int						ft_execvp(const char *file, char *const argv[]);
int						launch_exec(char **command);
void					get_commands(char *input, t_command_list *cmd_list);
void					load_shell(void);
void					print_commands(t_command_list *cmd);

#endif
