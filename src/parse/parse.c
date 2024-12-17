/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: akuijer <akuijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/24 16:00:52 by akuijer       #+#    #+#                 */
/*   Updated: 2024/04/29 16:41:20 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/parse.h"

static int32_t	parse_in2(char *line, char **str, int32_t *i, char **env)
{
	if (get_in(i, line, str) == -1)
	{
		return (-1);
	}
	if (find_token(str, env, NULL) == -1)
	{
		return (-1);
	}
	trim_str(str);
	return (0);
}

void	parse_in(char *line, t_pipex *info, int32_t *i, int32_t cmd_i)
{
	int32_t			status;
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
		ft_error3("Malloc error in", *info, line, NULL);
	}
}

void	parse_cmd(char *line, t_pipex *info, int32_t *i, int32_t cmd_i)
{
	char	*temp;

	temp = get_cmd(i, line);
	if (!temp)
	{
		ft_error3("Malloc error cmd", *info, line, NULL);
	}
	if (!temp || !temp[0])
	{
		free(temp);
		return ;
	}
	if (find_token(&temp, info->env, NULL) == -1)
	{
		ft_error3("Malloc error token", *info, line, NULL);
	}
	if (!temp || !temp[0])
	{
		free(temp);
		return ;
	}
	info->cmd[cmd_i].cmd = ft_strjoin2(info->cmd[cmd_i].cmd, temp, true);
	if (!info->cmd[cmd_i].cmd)
		ft_error3("Strjoin2 error", *info, line, NULL);
}

void	parse_out(char *line, t_pipex *info, int32_t *i, int32_t cmd_i)
{
	static int32_t	out_i;

	if (!info->cmd[cmd_i].out[0])
		out_i = 0;
	info->cmd[cmd_i].append = line[*i] == '>' && line[(*i) + 1] == '>';
	if (get_out(i, line, &info->cmd[cmd_i].out[out_i]) == -1)
	{
		ft_error3("Malloc error out", *info, line, NULL);
	}
	if (!info->cmd[cmd_i].out[out_i])
	{
		return ;
	}
	if (find_token(&info->cmd[cmd_i].out[out_i], info->env, NULL) == -1)
	{
		ft_error3("Malloc error out", *info, line, NULL);
	}
	trim_str(&info->cmd[cmd_i].out[out_i]);
	out_i++;
}
