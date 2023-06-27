/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/27 19:35:31 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2023/06/27 19:35:31 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "lexer.h"

int	is_delimiter(char c)
{
	int			i;
	static char	delimiter[7] = {DEL_DQUOTE, DEL_SQUOTE, DEL_PIPE, \
								DEL_DOLLAR, DEL_REDIN, DEL_REDOUT, DEL_SPACE};

	i = 0;
	while (i < 7)
	{
		if (c == delimiter[i])
			return (delimiter[i]);
		i++;
	}
	return (-1);
}

void	jump_delimiters(char *input, int *i, int curr_char_type)
{
	if (curr_char_type == DEL_DQUOTE || curr_char_type == DEL_SQUOTE)
	{
		(*i)++;
		while (input[*i] && input[*i] != curr_char_type)
			(*i)++;
	}
	else if (input[*i + 1] && \
	((curr_char_type == DEL_REDIN && input[*i + 1] == DEL_REDIN) \
	|| (curr_char_type == DEL_REDOUT && input[*i + 1] == DEL_REDOUT)))
		(*i)++;
	(*i)++;
}

void	insert_non_text_tokens(char *input, char **tokens_node, \
								int *j, int curr_char_type)
{
	int	start;

	if (curr_char_type == DEL_DQUOTE || curr_char_type == DEL_SQUOTE)
	{
		start = *j;
		(*j)++;
		while (input[*j] && input[*j] != curr_char_type)
			(*j)++;
		*tokens_node = ft_substr(input, start, (*j) + 1 - start);
	}
	else if (input[*j + 1] && \
	((curr_char_type == DEL_REDIN && input[*j + 1] == DEL_REDIN) \
	|| (curr_char_type == DEL_REDOUT && input[*j + 1] == DEL_REDOUT)))
	{
		*tokens_node = ft_substr(input, *j, 2);
		(*j)++;
	}
	else if (curr_char_type == DEL_PIPE || curr_char_type == DEL_DOLLAR \
	|| curr_char_type == DEL_REDIN || curr_char_type == DEL_REDOUT)
		*tokens_node = ft_substr(input, *j, 1);
	else if (curr_char_type == DEL_SPACE)
	{
		start = *j;
		while (input[*j] && input[*j] == DEL_SPACE)
			(*j)++;
		*tokens_node = ft_substr(input, start, (*j) - start);
		(*j)--;
	}
	if (!*tokens_node)
		ft_error(errno, strerror(errno));
	(*j)++;
}
