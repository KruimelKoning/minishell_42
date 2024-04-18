/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbartels <lbartels@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/01 16:15:49 by lbartels      #+#    #+#                 */
/*   Updated: 2024/04/17 14:59:33 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	get_pwds(char **env, int32_t *pwd, int32_t *oldpwd)
{
	int32_t	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp("PWD=", env[i], 4))
			*pwd = i;
		if (!ft_strncmp("OLDPWD=", env[i], 7))
			*oldpwd = i;
		i++;
	}
}

void	change_pwd(t_pipex info)
{
	int32_t	pwd;
	int32_t	oldpwd;
	char	cwd[256];
	char	*temp;
	
	get_pwds(info.env, &pwd, &oldpwd);
	temp = ft_strjoin("OLDPWD=", info.env[pwd] + 4);
	if (!temp)
		ft_error2("Malloc error", 1, info);
	free(info.env[oldpwd]);
	info.env[oldpwd] = temp;
	if (!getcwd(cwd, 255))
		ft_error2("Getcwd error", 1, info);
	temp = ft_strjoin("PWD=", cwd);
	if (!temp)
		ft_error2("Malloc error", 1, info);
	free(info.env[pwd]);
	info.env[pwd] = temp;
}

char	*get_path(char	**split_cmd, t_pipex info)
{
	char	*path;

	if (!split_cmd[1])
		path = ft_getenv("HOME", info.env);
	else if (split_cmd[1][0] == '~')
		path = ft_strjoin(ft_getenv("HOME", info.env), &split_cmd[1][1]);
	else
		path = ft_strdup(split_cmd[1]);
	return (path);
}

void	ft_cd(char **split_cmd, t_pipex info)
{
	char	*path;

	if (split_cmd[1] && split_cmd[2])
	{
		ft_error2("Too many arguments", 0, info);
		g_last_exit_code = 1;
		return ;
	}
	path = get_path(split_cmd, info);
	if (chdir(path) != 0)
	{
		ft_error(path, 0);
		g_last_exit_code = 1;
		return ;
	}
	change_pwd(info);
	free(path);
	free_info(&info, false);
	g_last_exit_code = 0;
}
