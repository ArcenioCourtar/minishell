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
# include <linux/limits.h> // LOOK INTO PATH_MAX, AND MAKING IT PORTABLE
# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

typedef struct s_cmdlst	t_cmdlst;
typedef struct s_data	t_data;
typedef struct s_envlst	t_envlst;

typedef struct s_exec
{
	char				path[PATH_MAX];
	int					fork_num;
	char				**path_list;
	size_t				path_maxlen;
	struct s_envlst		*exit_code;
	bool				path_avail;
	char				*cmd;
	t_cmdlst			*my_node;
	t_cmdlst			*first_node;
	int					in_out_fd[2];
}	t_exec;

void	finalize_cmd_list(t_cmdlst **list);
void	executor(t_data *dat);
void	assign_exit_val(t_envlst *exit_code, int errnum);
void	wait_for_all(t_data *dat);
void	free_path_list(t_exec *exec);
void	find_path(t_exec *exec);
void	restore_old_fds(t_exec *exec);
void	save_old_fds(t_exec *exec);
void	create_forks(t_data *dat, t_exec *exec);
void	exec_fork(t_data *dat, t_exec *exec);
void	run_builtin(t_data *dat, t_exec *exec);
void	create_heredocs(t_data *dat, t_exec *exec);
void	pipe_error(void);
void	sigint_pipe_cleanup(t_cmdlst *node);
void	post_fork_checks(t_data *dat, t_exec *exec, t_cmdlst *tmp);
void	create_forks_close_pipe(t_cmdlst *node);

bool	check_path(char *path);
bool	find_pathvar(char **envp, t_exec *exec);
bool	check_builtin(t_data *dat, t_cmdlst *node);

int		count_forks(t_cmdlst **list);
int		is_builtin(char builtin_index[BT_NUM][10], char *arg);
int		redirects(t_exec *exec);
int		heredoc_break_conditions(char *input, char *delim);

#endif