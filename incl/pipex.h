/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbartels <lbartels@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/06 16:43:52 by lbartels      #+#    #+#                 */
/*   Updated: 2024/04/18 15:57:09 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "minishell.h"

typedef struct vars
{
	int		i;
	int		file_in;
	int		file_out;
	int		status;
	pid_t	*p_id2;
	int		io[2];
}	t_vars;

void	execute(char *cmd, t_pipex info);
int		open_file(char *file, char flag, bool append, t_pipex info);

#endif