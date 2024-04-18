/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: akuijer <akuijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/28 12:05:53 by akuijer       #+#    #+#                 */
/*   Updated: 2024/04/18 17:50:25 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/parse.h"

static int32_t	parse_in2(char *line, char **str, int32_t *i, char **env)
{
	if (get_in(i, line, str) == -1)
	{
		return (-1);
	}
	if (find_token(str, env) == -1)
	{
		return (-1);
	}
	trim_str(str);
	return (0);
}

void	parse_in(char *line, t_pipex *info, int32_t *i, int32_t cmd_i)
{
	int32_t	status;
	static int32_t	in_i;

	if (!info->cmd[cmd_i].in[0])
		in_i = 0;
	status = 0;
	skip_space(i, line);
	if (line[*i] == '<' && line[(*i) + 1] == '<')
	{
		info->cmd[cmd_i].heredoc = true;
		status = parse_in2(line, &info->cmd[cmd_i].delim, i, info->env);
	}
	else if (line[*i] == '<')
	{
		info->cmd[cmd_i].heredoc = false;
		status = parse_in2(line, &info->cmd[cmd_i].in[in_i], i, info->env);
		in_i++;
	}
	if (status == -1)
	{
		ft_error2("Malloc error", 1, *info);
	}
	
}

void	parse_cmd(char *line, t_pipex *info, int32_t *i, int32_t cmd_i)
{
	char	*temp;
	
	temp = get_cmd(i, line);
	if (!temp)
	{
		ft_error2("Malloc error cmd", 1, *info);
	}
	if (!temp || !temp[0])
	{
		free(temp);
		return ;
	}
	if (find_token(&temp, info->env) == -1)
	{
		ft_error2("Malloc error token", 1, *info);
	}
	if (!temp || !temp[0])
	{
		free(temp);
		return ;
	}
	info->cmd[cmd_i].cmd = ft_strjoin2(info->cmd[cmd_i].cmd, temp);
	if (!info->cmd[cmd_i].cmd)
		ft_error2("Strjoin2 error", 1, *info);
}

void	parse_out(char *line, t_pipex *info, int32_t *i, int32_t cmd_i)
{
	static int32_t	out_i;

	if (!info->cmd[cmd_i].out[0])
		out_i = 0;
	info->cmd[cmd_i].append = line[*i] == '>' && line[(*i) + 1] == '>';
	if (get_out(i, line, &info->cmd[cmd_i].out[out_i]) == -1)
	{
		ft_error2("Malloc error", 1, *info);
	}
	if (!info->cmd[cmd_i].out[out_i])
	{
		return ;
	}
	if (find_token(&info->cmd[cmd_i].out[out_i], info->env) == -1)
	{
		ft_error2("Malloc error", 1, *info);
	}
	trim_str(&info->cmd[cmd_i].out[out_i]);
	out_i++;
}

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
		ft_error2("Malloc error", 1, *info);
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
		ft_error2("Malloc error", 1, *info);
	}
	while (line[i])
	{
		init_chunk(line, info, i, cmd_i);
		parse_chunk(line, info, &i, &cmd_i);
	}
}
