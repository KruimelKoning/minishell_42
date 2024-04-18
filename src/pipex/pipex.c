
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbartels <lbartels@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/11 15:10:20 by lbartels      #+#    #+#                 */
/*   Updated: 2024/04/10 14:54:57 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/pipex.h"

void	here_doc(t_pipex info, int32_t cmd_i)
{
	int		fd[2];
	char	*buffer;

	if (pipe(fd) == -1)
		ft_error2("Pipe error", 1, info);
	while (1)
	{
		ft_putstr_fd("pipe heredoc: ", 1);
		buffer = get_next_line(0);
		if (!ft_strncmp(buffer, info.cmd[cmd_i].delim, \
				ft_strlen(info.cmd[cmd_i].delim)) && ft_strlen(buffer) - 1 \
				== ft_strlen(info.cmd[cmd_i].delim))
		{
			free(buffer);
			break ;
		}
		ft_putstr_fd(buffer, fd[1]);
		free(buffer);
	}
	close(fd[1]);
	if (info.cmd[cmd_i].heredoc && dup2(fd[0], STDIN_FILENO) < 0)
		ft_error2("dup2 error", 1, info);
	close(fd[0]);
}

void	in_out(t_pipex info, int32_t cmd_i)
{
	int32_t	i;
	int32_t	file_in;
	int32_t	file_out;

	if (info.cmd[cmd_i].delim)
		here_doc(info, cmd_i);
	i = 0;
	while (info.cmd[cmd_i].out[i])
	{
		file_out = open_file(info.cmd[cmd_i].out[i], 'o', info.cmd[cmd_i].append, info);
		if (dup2(file_out, STDOUT_FILENO) == -1)
			ft_error2("dup2 error", 1, info);
		close(file_out);
		i++;
	}
	i = 0;
	while (info.cmd[cmd_i].in[i])
	{
		file_in = open_file(info.cmd[cmd_i].in[i], 'i', false, info);
		if (!info.cmd[cmd_i].heredoc && dup2(file_in, STDIN_FILENO) == -1)
			ft_error2("dup2 error", 1, info);
		close(file_in);
		i++;
	}
	if (cmd_i == info.cmd_count - 1)
		execute(info.cmd[cmd_i].cmd, info);
}

pid_t	ft_pipe(t_pipex info, int32_t cmd_i)
{
	pid_t	p_id;
	int		fd[2];

	if (pipe(fd) == -1)
		ft_error("pipe error", 1);
	p_id = fork();
	if (p_id == -1)
		ft_error("fork error", 1);
	if (!p_id)
	{
		close(fd[0]);
		if (!info.cmd[cmd_i].out[0] && dup2(fd[1], STDOUT_FILENO) == -1)
			ft_error2("dup2 error", 1, info);
		in_out(info, cmd_i);
		close(fd[1]);
		execute(info.cmd[cmd_i].cmd, info);
	}
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		ft_error2("dup2 error", 1, info);
	close(fd[0]);
	return (p_id);
}


int	pipex(t_pipex info)
{
	t_vars	vars;

	vars.io[0] = dup(STDIN_FILENO);
	vars.io[1] = dup(STDOUT_FILENO);
	vars.p_id2 = malloc(info.cmd_count * sizeof(pid_t));
	if (!vars.p_id2)
		ft_error2("Malloc error", 1, info);
	vars.i = -1;
	while (++vars.i < info.cmd_count - 1)
		vars.p_id2[vars.i] = ft_pipe(info, vars.i);
	vars.p_id2[vars.i] = fork();
	if (vars.p_id2[vars.i] == -1)
		ft_error("fork error", 1);
	if (!vars.p_id2[vars.i])
		in_out(info, vars.i);
	vars.i = 0;
	while (vars.i < info.cmd_count)
		waitpid(vars.p_id2[vars.i++], &vars.status, 0);
	free(vars.p_id2);
	if (dup2(vars.io[0], STDIN_FILENO) == -1 || dup2(vars.io[1], STDOUT_FILENO) == -1)
		ft_error2("backup dup2 error", 1, info);
	return (WEXITSTATUS(vars.status));
}
