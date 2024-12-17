/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbartels <lbartels@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/21 15:35:17 by lbartels      #+#    #+#                 */
/*   Updated: 2024/04/29 17:44:39 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	ctrl_c_handler(int signum)
{
	if (signum == SIGINT)
	{
		if (g_status != HEREDOC)
		{
			ft_putchar_fd('\n', 1);
		}
		if (g_status == PARENT)
		{
			rl_on_new_line();
		}
		rl_replace_line("", 0);
		rl_redisplay();
		g_last_exit_code = 130;
		if (g_status == HEREDOC)
			g_status = QUIT_HEREDOC;
	}
}

void	set_signal(void)
{
	struct sigaction	sa;

	sa.sa_handler = ctrl_c_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaddset(&sa.sa_mask, SIGINT);
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		ft_error("Sigaction error", 1);
	}
	signal(SIGQUIT, SIG_IGN);
}
