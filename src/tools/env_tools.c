/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_tools.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbartels <lbartels@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/04 15:36:59 by lbartels      #+#    #+#                 */
/*   Updated: 2024/04/29 14:47:28 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int32_t	ft_getenv_index(char *name, char **env)
{
	int32_t	i;
	char	*temp;

	i = 0;
	temp = ft_strjoin(name, "=");
	if (!temp)
		return (-2);
	while (env[i])
	{
		if (!ft_strncmp(env[i], temp, ft_strlen(temp)))
		{
			free(temp);
			return (i);
		}
		i++;
	}
	free(temp);
	return (-1);
}

char	*ft_getenv(char *name, char **env)
{
	int		i;
	size_t	len;

	i = 0;
	while (env[i])
	{
		len = ft_strllen(env[i], "=");
		if (!ft_strncmp(env[i], name, len) && len == ft_strlen(name))
		{
			return (env[i] + len + 1);
		}
		i++;
	}
	return (NULL);
}

void	init_shell_lvl(char ***env)
{
	int32_t	len;
	char	**temp;

	len = 0;
	while ((*env)[len])
		len++;
	temp = ft_realloc2(*env, (len + 1) * sizeof(char *), sizeof(char *));
	temp[len + 1] = ft_strdup("1");
	if (!temp[len + 1])
		free_and_throw("Malloc error", 1, *env, NULL);
	free((*env)[len]);
	*env = temp;
}

void	inc_shell_lvl(char ***env)
{
	int32_t	index;
	char	*temp;
	char	*temp2;
	char	*temp3;

	index = ft_getenv_index("SHLVL", *env);
	if (index == -1)
	{
		init_shell_lvl(env);
	}
	else
	{
		temp = ft_itoa(ft_atoi(&(*env)[index][6]) + 1);
		temp2 = ft_substr((*env)[index], 0, 6);
		temp3 = ft_strjoin2(temp2, temp, false);
		if (!temp3)
		{
			free_and_throw("Malloc error", 1, *env, NULL);
		}
		free((*env)[index]);
		(*env)[index] = temp3;
	}
}

char	**init_env(char **env)
{
	int		i;
	int		len;
	char	**result;

	i = 0;
	len = 0;
	while (env[len])
		len++;
	result = ft_calloc(len + 1, sizeof(char *));
	if (!result)
	{
		ft_error("Malloc error", 1);
	}
	while (env[i])
	{
		result[i] = ft_strdup(env[i]);
		if (!result[i])
		{
			free_2d(result);
			ft_error("Malloc error", 1);
		}
		i++;
	}
	return (result);
}
