/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   string_tools.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: akuijer <akuijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/28 13:18:41 by akuijer       #+#    #+#                 */
/*   Updated: 2024/04/29 16:36:24 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	trim_cmd(char **split_cmd)
{
	int32_t	i;

	i = 0;
	while (split_cmd[i])
	{
		trim_str(&split_cmd[i]);
		i++;
	}
}

void	skip_space(int *i, char *str)
{
	while (str[*i] == ' ')
	{
		(*i)++;
	}
}

void	check_quotes(bool *s_quote, bool *d_quote, int i, char *str)
{
	if (str[i] == '\'' && !*d_quote)
		*s_quote = !*s_quote;
	if (str[i] == '\"' && !*s_quote)
		*d_quote = !*d_quote;
}

size_t	ft_strllen(const char *str, const char *list)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!str)
		return (0);
	while (1)
	{
		j = 0;
		while (list[j])
		{
			if (str[i] == list[j])
			{
				return (i);
			}
			j++;
		}
		if (!str[i])
		{
			return (i);
		}
		i++;
	}
}

char	*ft_strjoin2(char *s1, char *s2, bool add_space)
{
	int		i;
	int		j;
	char	*result;

	i = -1;
	j = -1;
	if (!s1)
		s1 = ft_calloc(1, sizeof(char));
	if (!s1 || !s2)
		return (free(s1), free(s2), NULL);
	result = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1 + add_space, 1);
	if (!result)
		return (free(s1), free(s2), NULL);
	while (s1[++i])
	{
		result[i] = s1[i];
	}
	if (add_space)
		result[i++] = ' ';
	while (s2[++j])
	{
		result[i + j] = s2[j];
	}
	return (free(s1), free(s2), result);
}
