/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   smart_split.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: akuijer <akuijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/02 14:07:24 by akuijer       #+#    #+#                 */
/*   Updated: 2024/04/24 16:17:31 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static int	get_stringptr_length(char *str, char c, int32_t i)
{
	int32_t	count;
	bool	s_quote;
	bool	d_quote;

	count = 0;
	s_quote = false;
	d_quote = false;
	while (str[i])
	{
		check_quotes(&s_quote, &d_quote, i, str);
		while (str[i] == c)
			i++;
		if (str[i])
		{
			count++;
			check_quotes(&s_quote, &d_quote, i, str);
		}
		while (str[i] && (str[i] != c || s_quote || d_quote))
		{
			i++;
			check_quotes(&s_quote, &d_quote, i, str);
		}
	}
	return (count);
}

static int	get_len(char *str, char c, int32_t i)
{
	int32_t	start_i;
	bool	s_quote;
	bool	d_quote;

	s_quote = false;
	d_quote = false;
	while (str[i] == c && !s_quote && !d_quote)
	{
		check_quotes(&s_quote, &d_quote, i, str);
		i++;
	}
	start_i = i;
	while (str[i] && (str[i] != c || s_quote || d_quote))
	{
		check_quotes(&s_quote, &d_quote, i, str);
		i++;
	}
	return (i - start_i);
}

static void	fill_string(char *str_in, char *str_out, char c, int32_t *i)
{
	int32_t	j;
	bool	s_quote;
	bool	d_quote;

	j = 0;
	s_quote = false;
	d_quote = false;
	while (str_in[*i] && str_in[*i] == c)
	{
		check_quotes(&s_quote, &d_quote, *i, str_in);
		(*i)++;
	}
	while (str_in[*i])
	{
		check_quotes(&s_quote, &d_quote, *i, str_in);
		if (str_in[*i] == c && !s_quote && !d_quote)
		{
			break ;
		}
		str_out[j] = str_in[*i];
		(*i)++;
		j++;
	}
}

char	**no_command(void)
{
	char	**array;

	array = ft_calloc(2, sizeof(char *));
	array[0] = ft_strdup("\0");
	if (!array[0])
		return (NULL);
	return (array);
}

char	**smart_split(char *s, char c)
{
	int32_t	str_count;
	int32_t	i;
	int32_t	j;
	char	**str_array;

	if (!s)
		return (no_command());
	i = 0;
	j = 0;
	str_count = get_stringptr_length(s, c, 0);
	str_array = ft_calloc(str_count + 1, sizeof(char *));
	if (!str_array)
		return (0);
	while (s[i] && j < str_count)
	{
		str_array[j] = ft_calloc(get_len(s, c, i) + 1, sizeof(char));
		if (!str_array[j])
			return (free_2d(str_array), NULL);
		fill_string(s, str_array[j], c, &i);
		j++;
	}
	return (str_array);
}
