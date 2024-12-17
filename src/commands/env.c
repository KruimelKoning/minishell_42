/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: akuijer <akuijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/01 15:42:42 by akuijer       #+#    #+#                 */
/*   Updated: 2024/04/24 16:25:58 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	ft_env(char **split_cmd, t_pipex info, bool free_env)
{
	int32_t	i;

	i = 0;
	if (split_cmd[1])
	{
		free_2d(split_cmd);
		free_info(&info, free_env);
		ft_error("env cannot use flags", 1);
	}
	while (info.env[i])
	{
		ft_putendl_fd(info.env[i], STDOUT_FILENO);
		i++;
	}
	free_info(&info, free_env);
	g_last_exit_code = 0;
}
