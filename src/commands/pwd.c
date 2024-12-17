/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbartels <lbartels@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/20 15:24:21 by lbartels      #+#    #+#                 */
/*   Updated: 2024/04/24 17:57:49 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	ft_pwd(char **split_cmd, t_pipex info, bool free_env)
{
	char	*pwd;

	errno = 0;
	if (split_cmd[1] && split_cmd[1][0] == '-')
	{
		free_2d(split_cmd);
		ft_error2("pwd cannot use flags", 1, info);
	}
	pwd = ft_getenv("PWD", info.env);
	if (pwd == NULL)
	{
		ft_error2("getenv error", 1, info);
	}
	ft_putendl_fd(pwd, STDOUT_FILENO);
	free_info(&info, free_env);
	g_last_exit_code = 0;
}
