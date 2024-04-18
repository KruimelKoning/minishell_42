/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: akuijer <akuijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/28 12:07:43 by akuijer       #+#    #+#                 */
/*   Updated: 2024/04/18 16:10:53 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int32_t	get_in(int *i, char *str, char **in);
char	*get_cmd(int *i, char *str);
int32_t	get_out(int *i, char *str, char **out);

int32_t	find_token(char **str, char **env);
char	*trim_quotes(char *str);
int32_t	count_cmds(char *line);