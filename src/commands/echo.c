/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: akuijer <akuijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/01 15:44:28 by akuijer       #+#    #+#                 */
/*   Updated: 2024/04/24 16:22:54 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

bool	skip_flag(char *str)
{
	int32_t	i;
	bool	newline;

	i = 0;
	newline = true;
	if (!str)
		return (true);
	while (!ft_strncmp(str + i, "-n", 2))
	{
		newline = false;
		i += 2;
		while (str[i] == 'n')
		{
			i++;
		}
		if (str[i] != ' ' && str[i] != '\0')
			return (true);
		skip_space(&i, str);
	}
	return (newline);
}

bool	handle_flag(char **split_cmd, int32_t *i)
{
	bool	newline;

	newline = true;
	if (split_cmd[1])
	{
		newline = skip_flag(split_cmd[1]);
	}
	while (!newline)
	{
		(*i)++;
		if (skip_flag(split_cmd[*i]))
			break ;
	}
	return (newline);
}

void	ft_echo(char **split_cmd, t_pipex info, bool free_env)
{
	int32_t	i;
	int32_t	j;
	bool	newline;

	i = 1;
	j = 0;
	free_info(&info, free_env);
	errno = 0;
	newline = handle_flag(split_cmd, &i);
	while (split_cmd[i])
	{
		ft_putstr_fd(split_cmd[i] + j, 1);
		j = 0;
		i++;
		if (split_cmd[i])
		{
			ft_putchar_fd(' ', 1);
		}
	}
	if (newline)
		ft_putchar_fd('\n', 1);
	g_last_exit_code = 0;
}
