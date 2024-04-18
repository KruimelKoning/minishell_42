/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tools.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: akuijer <akuijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/15 13:11:06 by akuijer       #+#    #+#                 */
/*   Updated: 2024/04/18 15:07:24 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	ft_error(char *error_msg, char exit_val)
{
	ft_putstr_fd(RED, 2);
	if (errno == 0 && error_msg)
	{
		ft_putendl_fd(error_msg, 2);
	}
	else if (error_msg)
	{
		perror(error_msg);
	}
	ft_putstr_fd(WHITE, 2);
	errno = 0;
	if (exit_val)
	{
		rl_clear_history();
		exit(exit_val);
	}
}

void	ft_error2(char *error_msg, char exit_val, t_pipex info)
{
	free_info(&info, exit_val != 0);
	ft_error(error_msg, exit_val);
}

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

void	free_and_throw(char *err_msg, char exit_val, char **s1, char **s2)
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
	if (free_env && info->env)
	{
		free_2d(info->env);
		info->env = NULL;
	}
}
