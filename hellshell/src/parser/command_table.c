/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command_table.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/19 12:32:56 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2023/07/19 12:32:56 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "libft.h"

t_cmd	*cmdlst_new_node(char *command);
void	cmd_lstadd_back(t_cmd **cmd_lst_head, t_cmd *new_node);

int	args_count(t_token *t_lst)
{
	int	count;

	count = 0;
	t_lst = t_lst->next;
	while (t_lst && t_lst->type != TOK_PIPE)
	{
		while (t_lst && t_lst->type == TOK_SPACE)
			t_lst = t_lst->next;
		if (t_lst && t_lst->type != TOK_SPACE && t_lst->type != TOK_PIPE)
		{
			count++;
			t_lst = t_lst->next;
		}
	}
	ft_printf("args count: %i\n", count);
	return (count);
}

char	**get_cmd_args(t_token *t_lst)
{
	char	**args;
	int		argc;
	t_token	*tmp;
	int		i;

	tmp = t_lst;
	argc = args_count(tmp);
	args = (char **)malloc(sizeof(char *) * (argc + 1));
	if (!args)
		ft_error(errno, strerror(errno));
	i = 0;
	tmp = tmp->next;
	while (tmp && i < argc)
	{
		while (tmp && tmp->type == TOK_SPACE)
			tmp = tmp->next;
		args[i] = tmp->token;
		i++;
		tmp = tmp->next;
	}
	args[i] = NULL;
	return (args);
}

void	create_command_table(t_data *data, t_parser_data *p_data)
{
	t_token	*tmp_token_lst;
	t_cmd	*new_node;

	tmp_token_lst = *(data->t_lst);
	while (tmp_token_lst)
	{
		// add new node to cmd table
		new_node = cmdlst_new_node(tmp_token_lst->token);

		// add args to command table
		new_node->argv = get_cmd_args(tmp_token_lst);
		// add to command table
		cmd_lstadd_back(p_data->cmd_table, new_node);
		// iterate till pipe
		while (tmp_token_lst && tmp_token_lst->type != TOK_PIPE)
			tmp_token_lst = tmp_token_lst->next;
	}
	exit(EXIT_SUCCESS);
}
