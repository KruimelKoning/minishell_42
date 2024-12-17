/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   trim_quotes.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: akuijer <akuijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/10 14:15:10 by akuijer       #+#    #+#                 */
/*   Updated: 2024/04/22 17:44:40 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static void	trim_quotes(char *str, int32_t q1, int32_t q2)
{
	ft_memmove(&str[q1], &str[q1 + 1], q2 - q1 - 1);
	ft_memmove(&str[q2 - 1], &str[q2 + 1], ft_strlen(&str[q2 + 1]));
	ft_bzero(&str[ft_strlen(str) - 2], 2);
}

static void	find_quotes(char *str)
{
	int32_t	i;
	int32_t	quote_i;
	bool	s_quote;
	bool	d_quote;

	i = 0;
	quote_i = -1;
	s_quote = false;
	d_quote = false;
	while (str[i])
	{
		check_quotes(&s_quote, &d_quote, i, str);
		if (!s_quote && !d_quote && quote_i != -1)
		{
			trim_quotes(str, quote_i, i);
			quote_i = -1;
			i -= 2;
		}
		else if ((s_quote || d_quote) && quote_i == -1)
		{
			quote_i = i;
		}
		i++;
	}
}

void	trim_str(char **str)
{
	if (*str)
	{
		find_quotes(*str);
	}
}
