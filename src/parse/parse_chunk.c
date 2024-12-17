/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_chunk.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: akuijer <akuijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/28 12:05:53 by akuijer       #+#    #+#                 */
/*   Updated: 2024/04/24 16:38:35 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/parse.h"

void	parse_chunk(char *line, t_pipex *info, int32_t *i, int32_t *cmd_i)
{
	bool	s_quote;
	bool	d_quote;

	s_quote = false;
	d_quote = false;
	while (line[*i] && (line[*i] != '|' || s_quote || d_quote))
	{
		check_quotes(&s_quote, &d_quote, *i, line);
		skip_space(i, line);
		if (!s_quote && !d_quote && line[*i] == '<')
			parse_in(line, info, i, *cmd_i);
		else if (!s_quote && !d_quote && line[*i] == '>')
			parse_out(line, info, i, *cmd_i);
		else
			parse_cmd(line, info, i, *cmd_i);
		skip_space(i, line);
	}
	if (line[*i] == '|')
		(*i)++;
	(*cmd_i)++;
}

void	init_chunk(char *line, t_pipex *info, int32_t i, int32_t cmd_i)
{
	int32_t	in_count;
	int32_t	out_count;
	bool	s_quote;
	bool	d_quote;

	in_count = 0;
	out_count = 0;
	s_quote = false;
	d_quote = false;
	while (line[i] && (line[i] != '|' || s_quote || d_quote))
	{
		check_quotes(&s_quote, &d_quote, i, line);
		if (!s_quote && !d_quote && line[i] == '<' && line[i + 1] != '<')
			in_count++;
		if (!s_quote && !d_quote && line[i] == '>' && line[i + 1] != '>')
			out_count++;
		i++;
	}
	info->cmd[cmd_i].in = ft_calloc(in_count + 2, sizeof(char *));
	info->cmd[cmd_i].out = ft_calloc(out_count + 2, sizeof(char *));
	if (!info->cmd[cmd_i].in || !info->cmd[cmd_i].out)
		ft_error3("Malloc error", *info, line, NULL);
}

void	parse_all(char *line, t_pipex *info)
{
	int32_t	i;
	int32_t	cmd_i;

	i = 0;
	cmd_i = 0;
	*info = (t_pipex){NULL, 0, info->env};
	info->cmd_count = count_cmds(line) + 1;
	info->cmd = ft_calloc(info->cmd_count + 1, sizeof(t_command));
	if (!info->cmd)
	{
		ft_error3("Malloc error", *info, line, NULL);
	}
	while (line[i])
	{
		init_chunk(line, info, i, cmd_i);
		parse_chunk(line, info, &i, &cmd_i);
	}
}
