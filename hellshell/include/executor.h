/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/10 15:35:46 by acourtar      #+#    #+#                 */
/*   Updated: 2023/08/10 15:35:46 by acourtar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include "parser.h"

typedef struct s_cmdlst	t_cmdlst;
typedef struct s_data	t_data;

typedef struct s_exec
{
	int		fork_num;
	char	**path_list;
	bool	path_avail;
}	t_exec;

bool	check_path(char *path);
void	finalize_cmd_list(t_cmdlst **list);
void	executor(t_data *dat);

#endif