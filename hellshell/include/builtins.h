/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/28 12:07:17 by acourtar      #+#    #+#                 */
/*   Updated: 2023/06/28 12:07:17 by acourtar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <errno.h>
# include <string.h>
# include <stdio.h>
# include <stdbool.h>

t_envlist	*newnode_env(char *envp);
void		builtin_env(char **envp);
void		builtin_pwd(void);
void		builtin_cd(t_data *dat);
void		builtin_exit(void);
void		builtin_export(t_data *dat);

#endif