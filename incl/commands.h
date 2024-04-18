/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbartels <lbartels@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/20 16:13:13 by lbartels      #+#    #+#                 */
/*   Updated: 2024/04/17 14:58:44 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

void	ft_cd(char **split_cmd, t_pipex info);
void	ft_echo(char **split_cmd, t_pipex info);
void	ft_env(char **split_cmd, t_pipex info);
void	ft_exit(char **split_cmd, t_pipex info);
void	ft_export(char **split_cmd, t_pipex *info);
void	ft_pwd(char **split_cmd, t_pipex info);
void	ft_unset(char **split_cmd, t_pipex *info);

#endif