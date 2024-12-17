/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: akuijer <akuijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/24 15:54:23 by akuijer       #+#    #+#                 */
/*   Updated: 2024/04/29 15:24:13 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	ft_error(char *error_msg, uint8_t exit_val)
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

void	ft_error2(char *error_msg, uint8_t exit_val, t_pipex info)
{
	free_info(&info, exit_val != 0);
	ft_error(error_msg, exit_val);
}

void	ft_error3(char *error_msg, t_pipex info, void *free1, void *free2)
{
	if (free1)
		free(free1);
	if (free2)
		free(free2);
	ft_error2(error_msg, 1, info);
}

void	ft_error4(char *error_msg, uint8_t exit_val, t_pipex info, char **split)
{
	free_info(&info, true);
	free_2d(split);
	ft_error(error_msg, exit_val);
	rl_clear_history();
	exit(exit_val);
}
