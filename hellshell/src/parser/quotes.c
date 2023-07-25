/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quotes.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/24 12:24:22 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2023/07/24 12:24:22 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"
#include "libft.h"

enum e_statespace
{
	ST_NO_PREV_SPACE,
	ST_PREV_SPACE
};

enum e_statequote
{
	ST_DQUOTE,
	ST_SQUOTE
};

void	single_quote(t_token *token)
{
	if (token->prev->type == TOK_SPACE)
	{
		
	}
}

void	check_for_quotes(t_data *data)
{
	t_token	*tmp_lst;
	int		i;
	

	tmp_lst = *(data->t_lst);
	while (tmp_lst)
	{
		if (tmp_lst->type == TOK_DQUOTE)
			/*do something with that*/;
		else if (tmp_lst->type == TOK_SQUOTE)
			single_quote(tmp_lst);
		tmp_lst = tmp_lst->next;
	}
}
