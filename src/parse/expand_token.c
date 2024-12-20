/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_token.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: akuijer <akuijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 14:09:45 by akuijer       #+#    #+#                 */
/*   Updated: 2024/04/29 17:47:04 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

char	*get_token(char *str, int i, char **env)
{
	char	*temp;
	char	*token;

	temp = ft_substr(str, i + 1, ft_strllen(&str[i + 1], " \"\'"));
	if (!temp)
		return (NULL);
	token = ft_getenv(temp, env);
	free(temp);
	if (!token)
		token = ft_strdup("\0");
	else
		token = ft_strdup(token);
	return (token);
}

char	*handle_token(char *str, int i, char **env)
{
	char	*token;
	char	*result;
	int32_t	size_diff;
	int32_t	temp_size;

	token = get_token(str, i, env);
	if (!token)
		return (NULL);
	temp_size = ft_strllen(&str[i], " \"\'");
	size_diff = ft_strlen(token) - temp_size;
	if (size_diff > 0)
		result = ft_realloc2(str, ft_strlen(str) + 1, size_diff);
	else
		result = str;
	if (!result)
		return (free(token), NULL);
	ft_memmove(&result[i + ft_strlen(token)], &result[i + temp_size], \
			ft_strlen(&result[i + temp_size]));
	if (size_diff < 0)
		ft_bzero(&result[ft_strlen(str) + size_diff], -size_diff);
	ft_memcpy(&result[i], token, ft_strlen(token));
	free(token);
	return (result);
}

char	*handle_question_mark(char *str, int i)
{
	char	*result;
	char	*token;
	int32_t	token_len;

	token = ft_itoa(g_last_exit_code);
	if (!token)
		return (NULL);
	token_len = ft_strlen(token);
	result = ft_realloc2(str, ft_strlen(str) + 1, token_len - 2);
	if (!result)
	{
		free(token);
		return (NULL);
	}
	ft_memmove(&result[i + token_len - 1], &result[i + 1], \
			ft_strlen(result + i));
	ft_memmove(&result[i], token, token_len);
	free(token);
	return (result);
}

int32_t	find_token(char **str, char **env, char *temp)
{
	int		i;
	bool	s_quote;
	bool	d_quote;

	i = 0;
	s_quote = false;
	d_quote = false;
	while (*str && (*str)[i])
	{
		check_quotes(&s_quote, &d_quote, i, *str);
		if ((*str)[i] == '$' && !s_quote && (*str)[i + 1] \
				&& (*str)[i + 1] != ' ' && (*str)[i + 1] != '\"')
		{
			if ((*str)[i + 1] == '?')
				temp = handle_question_mark(*str, i);
			else
				temp = handle_token(*str, i, env);
			if (!temp)
				return (-1);
			*str = temp;
			i += ft_strllen(*str + i, "\'\" ") - 1;
		}
		i++;
	}
	return (0);
}
