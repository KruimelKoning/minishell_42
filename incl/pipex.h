/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbartels <lbartels@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/06 16:43:52 by lbartels      #+#    #+#                 */
/*   Updated: 2024/04/24 17:33:17 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "minishell.h"

typedef struct vars
{
	int32_t	i;
	int32_t	status;
	pid_t	p_id;
	int32_t	*fd;
}	t_vars;

void	execute(char *cmd, t_pipex info);
void	here_doc(t_pipex info, int32_t cmd_i);

#endif