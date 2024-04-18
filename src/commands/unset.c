/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbartels <lbartels@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/01 17:25:31 by lbartels      #+#    #+#                 */
/*   Updated: 2024/04/16 16:28:04 by akuijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	unset_block(char *var, t_pipex *info)
{
	int32_t	i;
	int32_t	len;
	void	*temp;

	i = -1;
	len = 0;
	temp = ft_strjoin(var, "=");
	if (!temp)
		ft_error2("Strjoin error", 1, *info);
	while (info->env[len])
	{
		if (!ft_strncmp(temp, info->env[len], ft_strlen(temp)))
			i = len;
		len++;
	}
	if (i == -1)
		return ;
	free(info->env[i]);
	ft_memmove(&info->env[i], &info->env[i + 1], (len - i) * sizeof(char *));
	temp = ft_realloc2(info->env, (len + 1) * sizeof(char *),
		-1 * (int)sizeof(char *));
	if (!temp)
		ft_error2("Realloc error", 1, *info);
	info->env = temp;
}

void	ft_unset(char **split_cmd, t_pipex *info)
{
	int32_t	i;

	i = 1;
	while (split_cmd[i])
	{
		unset_block(split_cmd[i], info);
		i++;
	}
	g_last_exit_code = 0;
	free_info(info, false);
}
