/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quotes.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/01 15:34:18 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2023/08/01 15:34:18 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"
#include "libft.h"

void	trim_quotes(t_toklst **token, enum e_token_type type, char *trim)
{
	char	*tmp;

	tmp = ft_strtrim((*token)->token, trim);
	free((*token)->token);
	(*token)->token = tmp;
	(*token)->type = type;
}

void	quote_join_back(t_toklst **token)
{
	// char		*tmp;

	// tmp = ft_strdup((*token)->prev->token);
	// free((*token)->prev->token);
	(*token)->prev->token = ft_strjoinfree((*token)->prev->token, (*token)->token);
	cmdlst_del_node(token);
}

void	quote_join_front(t_toklst **token)
{
	// char	*tmp;

	// tmp = ft_strdup((*token)->token);
	// free((*token)->token);
	(*token)->token = ft_strjoinfree((*token)->token, (*token)->next->token);
	*token = (*token)->next;
	cmdlst_del_node(token);
}

void	handle_single_quote(t_toklst **token, \
									enum e_state_space space_state)
{
	trim_quotes(token, TOK_NAME, "\'");
	if (space_state == NOSPACE)
		quote_join_back(token);
	if ((*token)->next && (*token)->next->type != TOK_SPACE && (*token)->next->type != TOK_SQUOTE && (*token)->next->type != TOK_DQUOTE)
		quote_join_front(token);
}

void	handle_double_quote(t_toklst **token, enum e_state_space space_state)
{
	trim_quotes(token, TOK_DQUOTE, "\"");
	if (check_for_dollar((*token)->token))
	{
		// expansion(token);
		ft_printf("\"expansion\"\n");
	}
	if (space_state == NOSPACE)
		quote_join_back(token);
	if ((*token)->next && (*token)->next->type != TOK_SPACE && (*token)->next->type != TOK_SQUOTE && (*token)->next->type != TOK_DQUOTE)
		quote_join_front(token);
}

void	handle_quotes(t_toklst **token)
{
	enum e_state_space	space_state;

	if ((*token)->prev && (*token)->prev->type == TOK_SPACE)
		space_state = SPACE;
	else if ((*token)->prev)
		space_state = NOSPACE;
	else
		space_state = FIRST;
	if ((*token)->type == TOK_SQUOTE)
		handle_single_quote(token, space_state);
	else if ((*token)->type == TOK_DQUOTE)
		handle_double_quote(token, space_state);
}

void	quotes(t_data *data)
{
	t_toklst	*tmp;

	tmp = *(data->t_lst);
	while (tmp)
	{
		if (tmp->type == TOK_DQUOTE || tmp->type == TOK_SQUOTE)
			handle_quotes(&tmp);
		else if (tmp->type == TOK_DOLLAR)
		{
			// expansion(&tmp);
			ft_printf("expansion\n");
			handle_quotes(&tmp);
		}
		tmp = tmp->next;
	}
}
