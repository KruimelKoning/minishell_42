/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbartels <lbartels@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/05 14:53:06 by lbartels      #+#    #+#                 */
/*   Updated: 2024/04/18 17:22:14 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"
#include "../../incl/commands.h"

bool	check_builtin(t_pipex *info)
{
	char	**split_cmd;

	if (info->cmd[1].cmd)
		return (false);
	split_cmd = smart_split(info->cmd[0].cmd, ' ');
	if (!split_cmd)
		ft_error2("Split error", 1, *info);
	trim_cmd(split_cmd);
	if (!ft_strncmp(split_cmd[0], "cd", 3))
		ft_cd(split_cmd, *info);
	else if (!ft_strncmp(split_cmd[0], "export", 7))
		ft_export(split_cmd, info);
	else if (!ft_strncmp(split_cmd[0], "exit", 5))
		ft_exit(split_cmd, *info);
	else if (!ft_strncmp(split_cmd[0], "unset", 6))
		ft_unset(split_cmd, info);
	else
	{
		free_2d(split_cmd);
		return (false);
	}
	free_2d(split_cmd);
	return (true);
}
