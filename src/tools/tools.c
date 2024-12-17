/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tools.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: akuijer <akuijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/15 13:11:06 by akuijer       #+#    #+#                 */
/*   Updated: 2024/04/29 15:24:34 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	free_2d(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_and_throw(char *err_msg, uint8_t exit_val, char **s1, char **s2)
{
	free_2d(s1);
	free_2d(s2);
	ft_error(err_msg, exit_val);
}

void	*ft_realloc2(void *ptr_in, int size, int add)
{
	void	*ptr_out;

	ptr_out = ft_calloc(size + add, 1);
	if (!ptr_out)
	{
		return (NULL);
	}
	if (add < 0)
	{
		ft_memcpy(ptr_out, ptr_in, size + add);
	}
	else
	{
		ft_memcpy(ptr_out, ptr_in, size);
	}
	free(ptr_in);
	return (ptr_out);
}

void	free_info(t_pipex *info, bool free_env)
{
	int32_t	i;

	i = 0;
	while (i < info->cmd_count)
	{
		free_2d(info->cmd[i].in);
		free(info->cmd[i].cmd);
		free_2d(info->cmd[i].out);
		free(info->cmd[i].delim);
		i++;
	}
	free(info->cmd);
	if (free_env && info->env)
	{
		free_2d(info->env);
		info->env = NULL;
	}
}

int	open_file(char *file, char flag, bool append)
{
	int	fd;

	fd = -1;
	if (flag == 'i')
		fd = open(file, O_RDONLY);
	else if (flag == 'o' && !append)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (flag == 'o' && append)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	return (fd);
}
