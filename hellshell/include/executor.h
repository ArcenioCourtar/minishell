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
# define MAX_PATH 4096// Should this be 1024 or 4096?
# include "parser.h"

typedef struct s_cmdlst	t_cmdlst;
typedef struct s_data	t_data;

typedef struct s_exec
{
	char		path[MAX_PATH];
	int			fork_num;
	char		**path_list;
	size_t		path_maxlen;
	bool		path_avail;
	char		*cmd;
	t_cmdlst	*my_node;
}	t_exec;

bool	check_path(char *path);
void	finalize_cmd_list(t_cmdlst **list);
void	executor(t_data *dat);
void	close_and_free(t_data *dat, t_exec *exec);
void	wait_for_all(int fork_amount);
bool	find_pathvar(char **envp, t_exec *exec);
int		count_forks(t_cmdlst **list);
void	create_forks(t_data *dat, t_exec *exec);
void	exec_fork(t_data *dat, t_exec *exec);
// maybe put in builtins header? also change arguments to just *dat?
int		is_builtin(char builtin_index[BT_NUM][10], char *arg);
void	run_builtin(t_data *dat, t_exec *exec);

#endif