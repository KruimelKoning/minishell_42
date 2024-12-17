/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: akuijer <akuijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/04 14:41:42 by akuijer       #+#    #+#                 */
/*   Updated: 2024/04/24 12:05:38 by akuijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static int32_t	check_char(char *line, int32_t i)
{
	bool	is_pipe;

	is_pipe = false;
	if (ft_strchr("<>", line[i]) && line[i] == line[i + 1])
	{
		i++;
	}
	if (ft_strchr("<|>", line[i]))
	{
		is_pipe = line[i] == '|';
		i++;
		skip_space(&i, line);
	}
	if (line[i] == '|' || (ft_strchr("<>", line[i]) && !is_pipe))
	{
		ft_putstr_fd("Invalid syntax near: \'", 2);
		ft_putchar_fd(line[i], 2);
		ft_putstr_fd("\'\n", 2);
		return (-1);
	}
	return (0);
}

int32_t	check_input(char *line)
{
	int32_t	i;
	bool	s_quote;
	bool	d_quote;

	i = 0;
	s_quote = false;
	d_quote = false;
	while (line[i])
	{
		check_quotes(&s_quote, &d_quote, i, line);
		if (!s_quote && !d_quote && check_char(line, i) == -1)
		{
			return (-1);
		}
		i++;
	}
	return (0);
}
