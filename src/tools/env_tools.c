/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_tools.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbartels <lbartels@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/04 15:36:59 by lbartels      #+#    #+#                 */
/*   Updated: 2024/04/17 16:48:07 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

char	*ft_getenv_start(char *name, char **env)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		temp = ft_substr(env[i], 0, j);
		if (!ft_strncmp(temp, name, ft_strlen(name)))
		{
			free(temp);
			return (env[i]);
		}
		free(temp);
		i++;
	}
	return (NULL);
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

char	*ft_getenv(char *name, char **env)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		temp = ft_substr(env[i], 0, j);
		if (!ft_strncmp(temp, name, ft_strlen(temp) + 1))
		{
			free(temp);
			return (env[i] + j + 1);
		}
		free(temp);
		i++;
	}
	return (NULL);
}
