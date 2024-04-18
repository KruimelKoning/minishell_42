/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbartels <lbartels@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/05 16:59:37 by lbartels      #+#    #+#                 */
/*   Updated: 2024/04/16 14:33:13 by akuijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

long	ft_atol(char *str)
{
	long	num;
	int		i;
	long	min;

	num = 0;
	i = 0;
	min = 1;
	if (ft_strlen(str) > 11)
		return (1);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			min = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - 48);
		i++;
	}
	num = num * min;
	return (num);
}

bool	check_str(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	if (str[0] == '-' || str[0] == '+')
	{
		i++;
	}
	if (str[i] == '\0')
		return (false);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	if (len > 19 || ((str[0] == '-' || str[0] == '+') && len > 20))
		return (false);
	if ((len == 19 && ft_strncmp(str, "9223372036854775807", 20) > 0)
		|| (len == 20 && ft_strncmp(str, "+9223372036854775807", 20) > 0)
		|| (len == 20 && ft_strncmp(str, "-9223372036854775808", 20) < 0))
		return (false);
	return (true);
}

void	ft_exit(char **split_cmd, t_pipex info)
{
	int	exit_code;

	ft_putendl_fd("exit", 1);
	exit_code = 0;
	if (split_cmd[1] && split_cmd[2])
	{
		ft_putendl_fd("exit: too many arguments", 2);
		exit_code = 1;
	}
	else if (split_cmd[1] && check_str(split_cmd[1]) == false)
	{
		ft_putendl_fd("exit: numeric argument required", 2);
		exit_code = 2;
	}
	else if (split_cmd[1])
	{
		exit_code = (uint8_t)ft_atol(split_cmd[1]);
	}
	free_info(&info, true);
	free_2d(split_cmd);
	exit(exit_code);
}
