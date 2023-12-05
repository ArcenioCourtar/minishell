/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exp_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/05 10:57:44 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2023/12/05 10:57:44 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "minishell.h"

int	heredoc_exception(t_data *data, t_toklst **token)
{
	t_toklst	*tmp;

	if ((*token)->type == TOK_DOLLAR)
	{
		if ((*token)->next && (*token)->next->type != TOK_SPACE)
		{
			(*token)->token = \
							ft_strjoin((*token)->token, (*token)->next->token);
			add_to_free_lst(data, (*token)->token);
			*token = (*token)->next;
			token_lstdel_node(token);
		}
		(*token)->type = TOK_NAME;
	}
	tmp = *token;
	while (tmp->prev && tmp->prev->type == TOK_SPACE)
		tmp = tmp->prev;
	if (tmp->prev && tmp->prev->type == TOK_HEREDOC)
	{
		if ((*token)->type == TOK_DQUOTE || (*token)->type == TOK_SQUOTE)
			trim_quotes(data, token, TOK_SQUOTE);
		return (1);
	}
	return (0);
}
