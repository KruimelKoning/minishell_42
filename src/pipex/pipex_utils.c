/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbartels <lbartels@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/08 17:24:37 by lbartels      #+#    #+#                 */
/*   Updated: 2024/04/29 16:15:12 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/pipex.h"
#include "../../incl/minishell.h"
#include "../../incl/commands.h"
#include "../../incl/parse.h"

void	get_here_doc(t_pipex info, int32_t cmd_i, int32_t *fd)
{
	char	*buffer;

	while (g_status != QUIT_HEREDOC)
	{
		ft_putstr_fd("> ", 1);
		buffer = get_next_line(STDIN_FILENO);
		if (!buffer)
		{
			ft_error2("gnl error", 1, info);
			close(fd[0]);
		}
		if (!ft_strncmp(buffer, info.cmd[cmd_i].delim,
				ft_strlen(info.cmd[cmd_i].delim)) && ft_strlen(buffer) - 1 \
				== ft_strlen(info.cmd[cmd_i].delim))
		{
			free(buffer);
			return ;
		}
		ft_putstr_fd(buffer, fd[1]);
		free(buffer);
	}
}

void	here_doc(t_pipex info, int32_t cmd_i)
{
	int		fd[2];

	g_status = HEREDOC;
	if (pipe(fd) == -1)
		ft_error2("pipe error", 1, info);
	close(fd[1]);
	get_here_doc(info, cmd_i, fd);
	if (dup2(fd[0], STDIN_FILENO) < 0)
		ft_error2("dup2 error", 1, info);
	close(fd[0]);
	if (g_status == QUIT_HEREDOC)
	{
		free_info(&info, true);
		exit(0);
	}
}

char	*find_path(char **split_cmd, t_pipex info, int32_t i)
{
	char	**full_path;
	char	*path;
	char	*ret;

	if (access(split_cmd[0], F_OK) == 0 && access(split_cmd[0], X_OK) == 0)
		return (split_cmd[0]);
	full_path = ft_split(ft_getenv("PATH", info.env), ':');
	if (!full_path)
		ft_error4("split error", 1, info, split_cmd);
	while (full_path && full_path[i])
	{
		path = ft_strjoin(full_path[i++], "/");
		ret = ft_strjoin(path, split_cmd[0]);
		free(path);
		if (!ret)
		{
			free_2d(full_path);
			ft_error4("strjoin error", 1, info, split_cmd);
		}
		if (access(ret, F_OK) == 0 && access(ret, X_OK) == 0)
			return (free_2d(full_path), ret);
		free(ret);
	}
	free_2d(full_path);
	return (NULL);
}

void	ft_execve(char **split_cmd, t_pipex info)
{
	if (!ft_strncmp(split_cmd[0], "echo", 5))
		ft_echo(split_cmd, info, true);
	else if (!ft_strncmp(split_cmd[0], "cd", 3))
		ft_cd(split_cmd, &info, true);
	else if (!ft_strncmp(split_cmd[0], "pwd", 4))
		ft_pwd(split_cmd, info, true);
	else if (!ft_strncmp(split_cmd[0], "export", 7))
		ft_export(split_cmd, &info, true);
	else if (!ft_strncmp(split_cmd[0], "unset", 6))
		ft_unset(split_cmd, &info, true);
	else if (!ft_strncmp(split_cmd[0], "env", 4))
		ft_env(split_cmd, info, true);
	else if (!ft_strncmp(split_cmd[0], "exit", 5))
		ft_exit(split_cmd, info);
	else
		return ;
	free_2d(split_cmd);
	clear_history();
	exit(g_last_exit_code);
}

void	execute(char *cmd, t_pipex info)
{
	char	**split_cmd;
	char	*path;

	split_cmd = smart_split(cmd, ' ');
	if (!split_cmd)
		ft_error2("split error execute", 1, info);
	trim_cmd(split_cmd);
	if (!split_cmd[0] || !split_cmd[0][0])
		ft_error4("", 0, info, split_cmd);
	ft_execve(split_cmd, info);
	path = find_path(split_cmd, info, 0);
	if (!path)
		ft_error4("command not found", 127, info, split_cmd);
	if (execve(path, split_cmd, info.env) == -1)
	{
		if (split_cmd[0] != path)
			free(path);
		ft_error4("command not found", 1, info, split_cmd);
	}
	free_info(&info, true);
	if (split_cmd[0] != path)
		free(path);
	free_2d(split_cmd);
	clear_history();
	exit(EXIT_SUCCESS);
}
