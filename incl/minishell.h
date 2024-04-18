/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbartels <lbartels@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/15 16:25:41 by lbartels      #+#    #+#                 */
/*   Updated: 2024/04/18 14:59:41 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define WHITE "\033[0;37m"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdint.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>

# include <dirent.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>

# include "../libft/libft.h"

# include <readline/readline.h>
# include <readline/history.h>

# include <signal.h>

typedef struct t_command
{
	char	**in;
	char	*cmd;
	char	**out;
	char	*delim;
	bool	heredoc;
	bool	append;
}	t_command;

typedef struct t_pipex
{
	t_command *cmd;
	int		cmd_count;
	char	**env;
}	t_pipex;

extern int32_t	g_last_exit_code;

// Execute:

int		pipex(t_pipex info);
bool	check_builtin(t_pipex *info);

// Error Management:

void	ft_error(char *error_msg, char exit_val);
void	ft_error2(char *error_msg, char exit_val, t_pipex info);
void	free_and_throw(char *err_msg, char exit_val, char **s1, char **s2);

// Memory Management:

void	*ft_realloc2(void *ptr_in, int size, int add);
char	**smart_split(char *s, char c);
void	free_2d(char **split);
void	free_info(t_pipex *info, bool free_env);

// String Manipulation:

void	skip_space(int *i, char *str);
size_t	ft_strllen(const char *str, const char *list);
char	*ft_strjoin2(char *s1, char *s2);
void	check_quotes(bool *s_quote, bool *d_quote, int i, char *str);
void	trim_cmd(char **split_cmd);

// Parsing:

void	parse_all(char	*line, t_pipex *info);
int		check_input(char *line);
char	*ft_getenv(char *name, char **env);
char	*ft_getenv_start(char *name, char **env);
void	trim_str(char **str);
void	trim_in_out(t_pipex *info);

// Initialisation:

void	set_signal(void);
char	**init_env(char **env);

#endif