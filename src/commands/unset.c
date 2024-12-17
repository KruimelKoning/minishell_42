/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbartels <lbartels@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/01 17:25:31 by lbartels      #+#    #+#                 */
/*   Updated: 2024/04/24 18:20:15 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

char	*unset_block(char *var, t_pipex *info)
{
	int32_t	i;
	int32_t	len;
	void	*temp;

	i = -1;
	len = 0;
	temp = ft_strjoin(var, "=");
	if (!temp)
		return ("Strjoin error");
	while (info->env[len])
	{
		if (!ft_strncmp(temp, info->env[len], ft_strlen(temp)))
			i = len;
		len++;
	}
	free(temp);
	if (i == -1)
		return (NULL);
	free(info->env[i]);
	ft_memmove(&info->env[i], &info->env[i + 1], (len - i) * sizeof(char *));
	temp = ft_realloc2(info->env, (len + 1) * sizeof(char *), -1 * 8);
	if (!temp)
		return ("Realloc error");
	info->env = temp;
	return (NULL);
}

void	ft_unset(char **split_cmd, t_pipex *info, bool free_env)
{
	int32_t	i;
	char	*str;

	i = 1;
	while (split_cmd[i])
	{
		str = unset_block(split_cmd[i], info);
		if (str)
		{
			free_2d(split_cmd);
			ft_error2(str, 1, *info);
		}
		i++;
	}
	g_last_exit_code = 0;
	free_info(info, free_env);
}
