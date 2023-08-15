/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quotes_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/07 12:13:16 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2023/08/07 12:13:16 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"
#include "libft.h"

void	trim_quotes(t_toklst **token, enum e_token_type type, char *trim)
{
	char	*tmp;

	tmp = ft_strtrim((*token)->token, trim);
	(*token)->token = tmp;
	(*token)->type = type;
}

void	quote_join(t_toklst **token, bool joinaddback)
{
	if (!*token)
		return ;
	if (joinaddback)
		(*token)->prev->token = ft_strjoinfree((*token)->prev->token, \
														(*token)->token);
	else
	{
		(*token)->token = ft_strjoinfree((*token)->token, \
													(*token)->next->token);
		*token = (*token)->next;
	}
	toklst_del_node(token);
}
