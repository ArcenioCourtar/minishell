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

void		builtin_env(char **envp);

#endif