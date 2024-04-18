/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbartels <lbartels@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/08 17:24:37 by lbartels      #+#    #+#                 */
/*   Updated: 2024/04/18 18:18:47 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/pipex.h"
#include "../../incl/minishell.h"
#include "../../incl/commands.h"
#include "../../incl/parse.h"

int	open_file(char *file, char flag, bool append, t_pipex info)
{
	int	fd;

	fd = -1;
	if (flag == 'i')
		fd = open(file, O_RDONLY);
	else if (flag == 'o' && !append)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (flag == 'o' && append)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
	{
		ft_error2("Error opening file", 1, info);
	}
	return (fd);
}

char	*find_path(char *cmd, t_pipex info)
{
	int		i;
	char	**full_path;
	char	*path;
	char	*ret;

	if (access(cmd, F_OK) == 0 && access(cmd, X_OK) == 0)
		return (cmd);
	full_path = ft_split(ft_getenv("PATH", info.env), ':');
	i = 0;
	while (full_path && full_path[i])
	{
		path = ft_strjoin(full_path[i], "/");
		ret = ft_strjoin(path, cmd);
		free(path);
		if (access(ret, F_OK) == 0 && access(ret, X_OK) == 0)
		{
			free_2d(full_path);
			return (ret);
		}
		free(ret);
		i++;
	}
	free_2d(full_path);
	return (NULL);
}

void	ft_execve(char **split_cmd, t_pipex info)
{
	if (!ft_strncmp(split_cmd[0], "echo", 5))
		ft_echo(split_cmd, info);
	else if (!ft_strncmp(split_cmd[0], "cd", 3))
		ft_cd(split_cmd, info);
	else if (!ft_strncmp(split_cmd[0], "pwd", 4))
		ft_pwd(split_cmd, info);
	else if (!ft_strncmp(split_cmd[0], "export", 7))
		ft_pwd(split_cmd, info);
	else if (!ft_strncmp(split_cmd[0], "unset", 6))
		ft_pwd(split_cmd, info);
	else if (!ft_strncmp(split_cmd[0], "env", 4))
		ft_env(split_cmd, info);
	else if (!ft_strncmp(split_cmd[0], "exit", 5))
		ft_pwd(split_cmd, info);
	else
		return ;
	exit(EXIT_SUCCESS);
}

void	execute(char *cmd, t_pipex info)
{
	char	**split_cmd;
	char	*path;

	if (!cmd[0])
		ft_error("empty command", 1);
	split_cmd = smart_split(cmd, ' ');
	if (!split_cmd)
		ft_error("split error execute", 1);
	trim_cmd(split_cmd);
	ft_execve(split_cmd, info);
	path = find_path(split_cmd[0], info);
	if (!path)
	{
		ft_error2("command not found", 127, info);
	}
	if (execve(path, split_cmd, info.env) == -1)
	{
		free(path);
		ft_error2("execve error", 1, info);
	}
	free_info(&info, true);
	exit(EXIT_SUCCESS);
}
