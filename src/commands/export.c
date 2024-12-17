/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbartels <lbartels@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/01 17:25:31 by lbartels      #+#    #+#                 */
/*   Updated: 2024/04/24 17:47:03 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	print_no_variable(t_pipex *info)
{
	int		i;

	i = 0;
	while (info->env[i])
	{
		printf("declare -x %s\n", info->env[i]);
		i++;
	}
	return ;
}

bool	check_existing(char *var, t_pipex *info, bool append, char **split_cmd)
{
	char	*temp;
	int32_t	env_i;

	temp = ft_substr(var, 0, ft_strllen(var, "+="));
	if (!temp)
		ft_error4("Malloc error", 1, *info, split_cmd);
	env_i = ft_getenv_index(temp, info->env);
	free(temp);
	if (env_i == -2)
		ft_error4("strjoin error", 1, *info, split_cmd);
	if (env_i == -1)
		return (false);
	if (!append)
		temp = ft_strdup(var);
	else
		temp = ft_strjoin(info->env[env_i], &var[ft_strllen(var, "=") + 1]);
	if (!temp)
		ft_error4("Malloc error", 1, *info, split_cmd);
	free(info->env[env_i]);
	info->env[env_i] = temp;
	return (true);
}

int32_t	check_var(char *var)
{
	if ((!ft_isalpha(var[0]) && var[0] != '_') || \
		ft_strllen(var, "=") > ft_strllen(var, " ~!@#%%^()-{}[];"))
	{
		g_last_exit_code = 1;
		ft_error("export: not a valid identifier", 0);
		return (-1);
	}
	if (!ft_strchr(var, '='))
		return (-1);
	if (ft_strllen(var, "=") && var[ft_strllen(var, "=") - 1] == '+')
		return (1);
	else
		return (0);
}

void	export_var(char *var, t_pipex *info, char **split_cmd)
{
	int32_t	i;
	int32_t	check;
	void	*temp;

	check = check_var(var);
	if (check < 0)
		return ;
	if (check_existing(var, info, check, split_cmd) == true)
		return ;
	i = 0;
	while (info->env[i])
		i++;
	temp = ft_realloc2(info->env, (i + 1) * sizeof(char *), 1 * sizeof(char *));
	if (!temp)
		ft_error4("realloc error", 1, *info, split_cmd);
	info->env = temp;
	if (check)
		ft_memmove(&var[ft_strllen(var, "+")], &var[ft_strllen(var, "+") + 1], \
			ft_strlen(&var[ft_strllen(var, "+")]));
	temp = ft_strdup(var);
	if (!temp)
		ft_error4("strdup error", 1, *info, split_cmd);
	info->env[i] = temp;
}

void	ft_export(char **split_cmd, t_pipex *info, bool free_env)
{
	int32_t	i;

	g_last_exit_code = 0;
	if (!split_cmd[1] || split_cmd[1][0] == '#')
	{
		print_no_variable(info);
		free_info(info, free_env);
		return ;
	}
	i = 1;
	while (split_cmd[i])
	{
		export_var(split_cmd[i], info, split_cmd);
		i++;
	}
	free_info(info, free_env);
}
