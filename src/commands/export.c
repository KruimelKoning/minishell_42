/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbartels <lbartels@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/01 17:25:31 by lbartels      #+#    #+#                 */
/*   Updated: 2024/04/11 17:50:45 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	print_no_variable(t_pipex *info)
{
	char	*temp;
	int		i;

	i = 0;
	while (info->env[i])
	{
		temp = ft_strjoin("declare -x ", info->env[i++]);
		ft_putendl_fd(temp, 1);
		free(temp);
	}
	free_info(info, false);
	return ;
}

bool	check_existing(char **split_cmd, t_pipex *info)
{
	char	*temp;
	char	*variable;

	temp = ft_substr(split_cmd[1], 0, ft_strllen(split_cmd[1], "="));
	if (!temp)
		ft_error("Malloc error", 1);
	variable = ft_getenv_start(temp, info->env);
	if (!variable)
	{
		free(temp);
		return (false);
	}
	free(temp);
	free(variable);
	variable = ft_strdup(split_cmd[1]);
	if (!variable)
		ft_error("Malloc error", 1);
	free_info(info, false);
	return (true);
}

void	ft_export(char **split_cmd, t_pipex *info)
{
	int		i;
	void	*temp;

	if (!split_cmd[1] || split_cmd[1][0] == '#')
	{
		print_no_variable(info);
		return ;
	}
	if ((!ft_isalpha(split_cmd[1][0]) && split_cmd[1][0] != '_') || ft_strllen(split_cmd[1], "=") > ft_strllen(split_cmd[1], "~!@#%%^()-+{}[];"))
	{
		g_last_exit_code = 1;
		ft_error2("export: not a valid identifier", 0, *info);
		return;
	}
	if (!ft_strchr(split_cmd[1], '='))
		return ;
	if (check_existing(split_cmd, info) == true)
		return ;
	i = 0;
	while (info->env[i])
		i++;
	temp = ft_realloc2(info->env, (i + 1) * sizeof(char *), 1 * sizeof(char *));
	if (!temp)
		ft_error2("Malloc error", 1, *info);
	info->env = temp;
	temp = ft_strdup(split_cmd[1]);
	if (!temp)
		ft_error2("Malloc error", 1, *info);
	info->env[i] = temp;
	free_info(info, false);
	g_last_exit_code = 0;
}
