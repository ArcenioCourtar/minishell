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

void	trim_quotes(t_toklst **token, enum e_token_types type, char *trim)
{
	char	*tmp;

	tmp = ft_strtrim((*token)->token, trim);
	free((*token)->token);
	(*token)->token = tmp;
	(*token)->type = type;
}

void	single_quote_join(t_toklst **token)
{
	char		*tmp;

	tmp = ft_strdup((*token)->prev->token);
	free((*token)->prev->token);
	(*token)->prev->token = ft_strjoinfree(tmp, (*token)->token);
	cmdlst_del_node(token);
}

void	handle_single_quote(t_toklst **token, \
									enum e_state_space space_state)
{
	trim_quotes(token, TOK_NAME, "\'");
	if (space_state == NOSPACE)
		single_quote_join(token);
}

void	handle_double_quote(t_toklst **token)
{
	trim_quotes(token, TOK_DQUOTE, "\"");
	//expand ofzo
}

void	handle_quotes(t_toklst **token)
{
	enum e_state_space	space_state;

	if ((*token)->prev && (*token)->prev->type == TOK_SPACE)
		space_state = SPACE;
	else if ((*token)->prev)
		space_state = NOSPACE;
	else
		space_state = NOTOK;
	if ((*token)->type == TOK_SQUOTE)
		handle_single_quote(token, space_state);
	else if ((*token)->type == TOK_DQUOTE)
		handle_double_quote(token);
}

void	quotes(t_data *data)
{
	t_toklst	*tmp;

	tmp = *(data->t_lst);
	while (tmp)
	{
		handle_quotes(&tmp);
		tmp = tmp->next;
	}
}
