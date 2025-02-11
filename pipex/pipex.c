/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbartels <lbartels@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/11 15:10:20 by lbartels      #+#    #+#                 */
/*   Updated: 2024/04/29 17:45:03 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/pipex.h"

void	in_file(t_pipex info, int32_t cmd_i)
{
	int32_t	i;
	int32_t	file_in;

	if (info.cmd[cmd_i].delim)
		here_doc(info, cmd_i);
	i = 0;
	while (info.cmd[cmd_i].in[i])
	{
		file_in = open_file(info.cmd[cmd_i].in[i], 'i', false);
		if (file_in == -1)
		{
			ft_error2("open error", 1, info);
		}
		if (!info.cmd[cmd_i].heredoc && dup2(file_in, STDIN_FILENO) == -1)
		{
			ft_error2("dup2 error", 1, info);
		}
		close(file_in);
		i++;
	}
}

void	out_file(t_pipex info, int32_t cmd_i)
{
	int32_t	i;
	int32_t	file_out;

	i = 0;
	while (info.cmd[cmd_i].out[i])
	{
		file_out = open_file(info.cmd[cmd_i].out[i], \
			'o', info.cmd[cmd_i].append);
		if (file_out == -1)
		{
			ft_error2("open error", 1, info);
		}
		if (dup2(file_out, STDOUT_FILENO) == -1)
		{
			ft_error2("dup2 error", 1, info);
		}
		close(file_out);
		i++;
	}
}

void	redirect(t_pipex info, int32_t cmd_i, int32_t *in, int32_t *out)
{
	in_file(info, cmd_i);
	out_file(info, cmd_i);
	if (in && !info.cmd[cmd_i].in[0] && !info.cmd[cmd_i].delim)
	{
		close(in[1]);
		if (!info.cmd[cmd_i].delim && dup2(in[0], STDIN_FILENO) == -1)
			ft_error2("dup2 error", 1, info);
		close(in[0]);
		free(in);
	}
	if (out && !info.cmd[cmd_i].out[0])
	{
		close(out[0]);
		if (!info.cmd[cmd_i].out[0] && dup2(out[1], STDOUT_FILENO) == -1)
			ft_error2("dup2 error", 1, info);
		close(out[1]);
		free(out);
	}
}

int32_t	*ft_pipe(t_pipex info, int32_t cmd_i, int32_t *in)
{
	pid_t	p_id;
	int32_t	*out;

	out = ft_calloc(2, sizeof(int32_t));
	if (!out)
		ft_error3("calloc error", info, in, out);
	if (pipe(out) == -1)
		ft_error3("pipe error", info, in, out);
	p_id = fork();
	if (p_id == -1)
		ft_error3("fork error", info, in, out);
	if (!p_id)
	{
		redirect(info, cmd_i, in, out);
		execute(info.cmd[cmd_i].cmd, info);
	}
	if (in)
	{
		close(in[0]);
		close(in[1]);
		free(in);
	}
	if (info.cmd[cmd_i].delim)
		waitpid(p_id, NULL, 0);
	return (out);
}

int	pipex(t_pipex info)
{
	t_vars	vars;

	g_status = COMMAND;
	vars = (t_vars){-1, 0, 0, NULL};
	while (++vars.i < info.cmd_count - 1)
		vars.fd = ft_pipe(info, vars.i, vars.fd);
	vars.p_id = fork();
	if (vars.p_id == -1)
		ft_error2("fork error", 1, info);
	if (!vars.p_id)
	{
		redirect(info, vars.i, vars.fd, NULL);
		execute(info.cmd[vars.i].cmd, info);
	}
	if (vars.fd)
	{
		close(vars.fd[0]);
		close(vars.fd[1]);
		free(vars.fd);
	}
	waitpid(vars.p_id, &vars.status, 0);
	while (wait(NULL) != -1)
		;
	return (WEXITSTATUS(vars.status));
}
