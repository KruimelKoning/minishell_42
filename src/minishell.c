/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: akuijer <akuijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/15 13:01:41 by akuijer       #+#    #+#                 */
/*   Updated: 2024/04/18 17:50:54 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

	// for (int i = 0; i < info->cmd_count; i++)
	// 	printf("%s %s %s\n\n", info->cmd[i].in[0], info->cmd[i].cmd, info->cmd[i].out[0]);

int32_t	g_last_exit_code;

void	handle_prompt(char *line, t_pipex *info)
{
	//check_input(line);
	parse_all(line, info);
	if (!info->cmd[0].cmd || !info->cmd[0].cmd[0])
	{
		free_info(info, false);
		g_last_exit_code = 0;
		return ;
	}
	if (check_builtin(info) == true)
		return ;
	g_last_exit_code = pipex(*info);
	free_info(info, false);

}

void	loop(char **env)
{
	char	*line;
	t_pipex	info;

	info.env = env;
	while (1)
	{
		line = readline("minishell:	");
		if (!line)
		{
			rl_clear_history();
			free_2d(info.env);
			ft_error("error reading line", 1);
		}
		add_history(line);
		handle_prompt(line, &info);
		free(line);
	}
	rl_clear_history();
}

int	main(int argc, char **argv, char **env)
{
	char	**env_cpy;

	if (argc != 1 || argv[1])
	{
		ft_error("Minishell doesn't take arguments\n", 1);
	}
	set_signal();
	env_cpy = init_env(env);
	loop(env_cpy);
}
