/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_input.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbartels <lbartels@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/20 15:26:17 by lbartels      #+#    #+#                 */
/*   Updated: 2024/04/18 17:40:11 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/parse.h"

int32_t	count_cmds(char *line)
{
	int32_t	i;
	int32_t	count;
	bool	s_quote;
	bool	d_quote;

	i = 0;
	count = 0;
	s_quote = false;
	d_quote = false;
	while (line[i])
	{
		check_quotes(&s_quote, &d_quote, i, line);
		if (line[i] == '|' && !s_quote && !d_quote)
			count++;
		i++;
	}
	return (count);
}

int32_t	get_in(int *i, char *str, char **in)
{
	int		start_i;
	bool	s_quote;
	bool	d_quote;

	s_quote = false;
	d_quote = false;
	skip_space(i, str);
	while (str[*i] == '<')
		(*i)++;
	skip_space(i, str);
	start_i = *i;
	while (str[*i] && (!ft_strchr(" <|>", str[*i]) || s_quote || d_quote))
	{
		check_quotes(&s_quote, &d_quote, *i, str);
		(*i)++;
	}
	if (start_i != *i)
	{
		*in = ft_substr(str, start_i, (*i) - start_i);
		if (!*in)
			return (-1);
	}
	return (0);
}

char	*get_cmd(int *i, char *str)
{
	int		start_i;
	bool	s_quote;
	bool	d_quote;

	s_quote = false;
	d_quote = false;
	skip_space(i, str);
	if (str[*i] == '|')
		(*i)++;
	skip_space(i, str);
	start_i = *i;
	while (str[*i] && (!ft_strchr("<|>", str[*i]) || s_quote || d_quote))
	{
		check_quotes(&s_quote, &d_quote, *i, str);
		(*i)++;
	}
	return (ft_substr(str, start_i, (*i) - start_i));
}

int32_t	get_out(int *i, char *str, char **out)
{
	int		start_i;
	bool	s_quote;
	bool	d_quote;

	s_quote = false;
	d_quote = false;
	skip_space(i, str);
	while (str[*i] == '>')
		(*i)++;
	skip_space(i, str);
	start_i = *i;
	while (str[*i] && ((!ft_strchr(" <|>", str[*i])) || s_quote || d_quote))
	{
		check_quotes(&s_quote, &d_quote, *i, str);
		(*i)++;
	}
	if (start_i != *i)
	{
		*out = ft_substr(str, start_i, (*i) - start_i);
		if (!*out)
			return (-1);
	}
	return (0);
}
