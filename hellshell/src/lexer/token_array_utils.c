/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_array_utils.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/27 19:35:31 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2023/06/27 19:35:31 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
		if (ft_iswhitespace(c))
			return (DEL_SPACE);
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

static int	get_quote_token_len(char *input, int *j, \
						int curr_char_type, int substr_start)
{
	int	substr_len;

	(*j)++;
	while (input[*j] && input[*j] != curr_char_type)
		(*j)++;
	substr_len = (*j) + 1 - substr_start;
	return (substr_len);
}

static int	get_space_token_len(char *input, int *j, int substr_start)
{
	int	substr_len;

	while (input[*j] && input[*j] == DEL_SPACE)
		(*j)++;
	substr_len = (*j) - substr_start;
	(*j)--;
	return (substr_len);
}

void	insert_non_text_tokens(char *input, char **tokens_node, \
								int *j, int curr_char_type)
{
	int	substr_start;
	int	substr_len;

	substr_start = *j;
	if (curr_char_type == DEL_DQUOTE || curr_char_type == DEL_SQUOTE)
		substr_len = get_quote_token_len(input, j, \
											curr_char_type, substr_start);
	else if (curr_char_type == DEL_SPACE)
		substr_len = get_space_token_len(input, j, substr_start);
	else if (input[*j + 1] && (curr_char_type == DEL_REDIN || \
			curr_char_type == DEL_REDOUT) && input[*j + 1] == curr_char_type)
	{
		substr_len = 2;
		(*j)++;
	}
	else
		substr_len = 1;
	*tokens_node = ft_substr(input, substr_start, substr_len);
	if (!*tokens_node)
		ft_error(errno, strerror(errno));
	(*j)++;
}
