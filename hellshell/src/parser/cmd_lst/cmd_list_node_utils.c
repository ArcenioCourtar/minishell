/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_list_node_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/26 15:26:30 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2023/07/26 15:26:30 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "libft.h"
#include "lexer.h"

int	count_redirs(t_toklst *token)
{
	t_toklst	*tmp;
	int			count;

	tmp = token;
	count = 0;
	while (tmp && tmp->type != TOK_PIPE)
	{
		if (is_redirect(tmp->type))
		{
			count++;
			tmp = tmp->next;
			while (tmp && tmp->type == TOK_SPACE)
				tmp = tmp->next;
			if (!tmp)
				break ;
		}
		tmp = tmp->next;
	}
	return (count);
}

void	skip_redirects(t_toklst **token)
{
	*token = (*token)->next;
	while ((*token)->type == TOK_SPACE)
		*token = (*token)->next;
	*token = (*token)->next;
}

int	argv_count(t_toklst *t_lst)
{
	int	count;

	count = 0;
	while (t_lst && t_lst->type != TOK_PIPE)
	{
		while (t_lst && t_lst->type == TOK_SPACE)
			t_lst = t_lst->next;
		if (t_lst && is_redirect(t_lst->type))
			skip_redirects(&t_lst);
		if (t_lst && t_lst->type != TOK_SPACE && t_lst->type != TOK_PIPE)
		{
			count++;
			t_lst = t_lst->next;
		}
	}
	return (count);
}

bool	is_redirect(enum e_token_type type)
{
	if (type == TOK_REDIN || type == TOK_REDOUT || \
		type == TOK_REDAPPEND || type == TOK_HEREDOC)
		return (true);
	else
		return (false);
}
