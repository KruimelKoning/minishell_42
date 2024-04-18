/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: akuijer <akuijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/04 14:41:42 by akuijer       #+#    #+#                 */
/*   Updated: 2024/04/05 14:48:33 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	check_input(char *line)
{
	int		i;
	int		arrow_left;
	int		arrow_rgth;
	bool	s_quote;
	bool	d_quote;

	i = 0;
	arrow_left = 0;
	arrow_rgth = 0;
	s_quote = false;
	d_quote = false;
	while (line[i])
	{
		check_quotes(&s_quote, &d_quote, i, line);
		if (line[i] == '<' && !s_quote && !d_quote)
			arrow_left++;
		else if (line[i] == '>' && !s_quote && !d_quote)
			arrow_rgth++;
		i++;
	}
	if (arrow_left > 2 || (arrow_left == 2 && ft_strchr(line, '<')[1] != '<'))
		return (ft_putstr_fd("invalid syntax near '<'", 2), 2);
	if (arrow_rgth > 2 || (arrow_rgth == 2 && ft_strchr(line, '>')[1] != '>'))
		return (ft_putstr_fd("invalid syntax near '>'", 2), 2);
	return (0);
}
