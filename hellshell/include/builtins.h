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

void		builtin_env(t_data *dat, t_exec *exec);
void		builtin_pwd(t_data *dat, t_exec *exec);
void		builtin_cd(t_data *dat, t_exec *exec);
void		builtin_exit(t_data *dat, t_exec *exec);
void		builtin_export(t_data *dat, t_exec *exec);
void		builtin_unset(t_data *dat, t_exec *exec);
void		builtin_echo(t_data *dat, t_exec *exec);

bool		change_existing_val(t_envlst *node, char *var);
bool		change_existing_val_alt(t_envlst *node, char *val);
bool		identifier_check(char *arg);

t_envlst	*check_var_existence(t_envlst *list, char *var);

#endif