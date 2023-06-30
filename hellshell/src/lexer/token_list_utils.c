/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_list_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/28 15:10:24 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2023/06/28 15:10:24 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

t_token	*tlst_new_node(char *token)
{
	t_token	*new_node;

	new_node = (t_token *)malloc(sizeof(t_token));
	if (!new_node)
		ft_error(errno, strerror(errno));
	new_node->token = token;
	new_node->type = get_token_type(token);
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

static t_token	*token_lstlast(t_token *t_lst)
{
	if (!t_lst)
		return (NULL);
	else if (!t_lst->next)
		return (t_lst);
	else
		while (t_lst->next)
			t_lst = t_lst->next;
	return (t_lst);
}

void	token_lstadd_back(t_token **t_lst_head, t_token *new_node)
{
	t_token	*tmp;

	if (!*t_lst_head)
	{
		*t_lst_head = new_node;
		return ;
	}
	else
	{
		tmp = token_lstlast(*t_lst_head);
		tmp->next = new_node;
		new_node->prev = tmp;
	}
}

static int	is_equal_token(char *token)
{
	int	i;

	if (!ft_isalpha(token[0]))
		return (0);
	i = 0;
	while (token[i])
	{
		if (token[i] == '=')
			break ;
		i++;
	}
	if (token[i] != '=')
		return (0);
	i--;
	while (i >= 0)
	{
		if (!ft_isalnum(token[i]) && token[i] != '_')
			return (0);
		i--;
	}
	return (1);
}

enum e_token_types	get_token_type(char *token)
{
	if (token[0] == TOK_DQUOTE || token[0] == TOK_SQUOTE || \
	token[0] == TOK_PIPE || token[0] == TOK_DOLLAR || token[0] == TOK_SPACE)
		return ((enum e_token_types)token[0]);
	else if (token[0] == TOK_REDIN)
	{
		if (token[1] == TOK_REDIN)
			return (TOK_HEREDOC);
		else
			return (TOK_REDIN);
	}
	else if (token[0] == TOK_REDOUT)
	{
		if (token[1] == TOK_REDOUT)
			return (TOK_REDAPPEND);
		else
			return (TOK_REDOUT);
	}
	else if (is_equal_token(token))
		return (TOK_EQUAL);
	else
		return (TOK_NAME);
}
