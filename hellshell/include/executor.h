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
typedef struct s_envlst	t_envlst;


typedef struct s_exec
{
	char				path[MAX_PATH];
	int					fork_num;
	char				**path_list;
	size_t				path_maxlen;
	struct s_envlst		*exit_code;
	bool				path_avail;
	char				*cmd;
	t_cmdlst			*my_node;
	int					in_out_fd[2];
}	t_exec;

bool	check_path(char *path);
void	finalize_cmd_list(t_cmdlst **list);
void	executor(t_data *dat);
bool	find_pathvar(char **envp, t_exec *exec);
int		count_forks(t_cmdlst **list);
void	create_forks(t_data *dat, t_exec *exec);
void	exec_fork(t_data *dat, t_exec *exec);
// maybe put in builtins header? also change arguments to just *dat?
int		is_builtin(char builtin_index[BT_NUM][10], char *arg);
void	run_builtin(t_data *dat, t_exec *exec);
int		redirects(t_exec *exec, bool parent);
void	assign_exit_val(t_envlst *exit_code, int errnum);
void	wait_for_all(t_data *dat);
void	close_all_pipes(t_data *dat);
void	free_path_list(t_exec *exec);

void	msg_err_exit(char *msg1, char *msg2, int errnum);
void	msg_err_noexit(char *msg1, char *msg2, int errnum);
void	msg_err_cust_exit(char *msg1, char *msg2, char *errmsg, int errnum);
void	msg_err_cust_noexit(char *msg1, char *msg2, char *errmsg);

#endif