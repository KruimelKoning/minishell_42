/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: akuijer <akuijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/15 13:01:41 by akuijer       #+#    #+#                 */
/*   Updated: 2024/04/29 16:17:53 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int32_t	g_last_exit_code;
int8_t	g_status;

void	handle_prompt(char *line, t_pipex *info)
{
	if (check_input(line) == -1)
	{
		ft_error("Invalid input", 0);
		g_last_exit_code = 1;
		return ;
	}
	parse_all(line, info);
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
	while (true)
	{
		g_status = PARENT;
		line = readline("minishell: ");
		if (!line)
		{
			rl_clear_history();
			free_2d(info.env);
			ft_putendl_fd("exit", 1);
			exit(0);
		}
		add_history(line);
		if (line[0])
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
	inc_shell_lvl(&env_cpy);
	loop(env_cpy);
}
