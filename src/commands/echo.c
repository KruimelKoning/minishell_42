/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: akuijer <akuijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/01 15:44:28 by akuijer       #+#    #+#                 */
/*   Updated: 2024/04/11 17:51:02 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

bool	parse_flag(char **split_cmd, int *index)
{
	int	i;
	int	j;

	i = *index;
	while (split_cmd[i] && split_cmd[i][0] == '-')
	{
		j = 1;
		while (split_cmd[i][j] == 'n')
		{
			j++;
		}
		if (split_cmd[i][j] != '\0')
		{
			return (false);
		}
		i++;
	}
	(*index) = i;
	return (true);
}

void	ft_echo(char **split_cmd, t_pipex info)
{
	int		i;
	bool	n;

	free_info(&info, true);
	errno = 0;
	n = (split_cmd[1] && !ft_strncmp(split_cmd[1], "-n", 3));
	i = 1 + n;
	if (parse_flag(split_cmd, &i) == false)
	{
		free_2d(split_cmd);
		ft_error("invalid flags, echo only uses -n", 1);
	}
	while (split_cmd[i])
	{
		ft_putstr_fd(split_cmd[i], 1);
		i++;
		if (split_cmd[i])
		{
			ft_putchar_fd(' ', 1);
		}
	}
	if (!n)
		ft_putchar_fd('\n', 1);
	free_2d(split_cmd);
	g_last_exit_code = 0;
}
