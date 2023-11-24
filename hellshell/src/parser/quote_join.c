/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_join.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/24 14:17:43 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2023/11/24 14:17:43 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "libft.h"

/**
 * @brief joins the token with the next or previous token
 * @param data pointer to the program data struct
 * @param token pointer to the token to join
 * @param joinaddback if true, join with previous token, else join with the next
 */
void	quote_join(t_data *data, t_toklst **token, bool joinaddback)
{
	if (!*token)
		return ;
	if (joinaddback)
	{
		(*token)->prev->token = ft_strjoin((*token)->prev->token, \
														(*token)->token);
		add_to_free_lst(data, (*token)->prev->token);
		if ((*token)->next)
		{
			token_lstdel_node(token);
			*token = (*token)->prev;
		}
		else
			token_lstdel_node(token);
	}
	else
	{
		(*token)->token = ft_strjoin((*token)->token, (*token)->next->token);
		add_to_free_lst(data, (*token)->token);
		*token = (*token)->next;
		token_lstdel_node(token);
	}
}
