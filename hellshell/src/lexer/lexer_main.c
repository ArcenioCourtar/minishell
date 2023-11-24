/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_main.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/28 13:26:01 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2023/06/28 13:26:01 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "lexer.h"

/**
 * @brief counts the number of tokens in the input
 * @param input pointer to the input string
 * @return number of tokens
 */
static int	token_counter(char *input)
{
	int	i;
	int	count;
	int	curr_char_type;

	count = 0;
	i = 0;
	while (input && input[i])
	{
		curr_char_type = is_delimiter(input[i]);
		count++;
		if (curr_char_type < 0)
			while (input[i] && is_delimiter(input[i]) < 0)
				i++;
		else if (curr_char_type == DEL_SPACE)
			while (input[i] && is_delimiter(input[i]) == DEL_SPACE)
				i++;
		else if (curr_char_type >= 0)
			jump_delimiters(input, &i, curr_char_type);
	}
	return (count);
}

/**
 * @brief inserts a token in the token array
 * @param input pointer to the input string
 * @param tokens pointer to the token array
 * @param token_count number of tokens
 */
static void	insert_tokens_in_array(char *input, char **tokens, int token_count)
{
	int	i;
	int	j;
	int	start;
	int	curr_char_type;

	i = 0;
	j = 0;
	while (i < token_count)
	{
		curr_char_type = is_delimiter(input[j]);
		if (curr_char_type < 0)
		{
			start = j;
			while (input[j] && is_delimiter(input[j]) < 0)
				j++;
			tokens[i] = ft_substr(input, start, j - start);
			if (!tokens[i])
				ft_error(errno, strerror(errno));
		}
		else if (curr_char_type >= 0)
			insert_non_text_tokens(input, &tokens[i], &j, curr_char_type);
		i++;
	}
	tokens[i] = NULL;
}

/**
 * @brief converts the input string to a token array
 * @param data pointer to the data struct
 * @param input pointer to the input string
 * @return pointer to the token array
 */
static char	**input_to_token_array(t_data *data, char *input)
{
	char	**tokens;
	int		token_count;

	token_count = token_counter(input);
	data->tok_count = token_count;
	tokens = malloc(sizeof(char *) * (token_count + 1));
	if (!tokens)
		ft_error(errno, strerror(errno));
	insert_tokens_in_array(input, tokens, token_count);
	return (tokens);
}

/**
 * @brief converts the token array to a token list
 * @param data pointer to the data struct
 * @param tokens pointer to the token array
 */
static void	token_array_to_list(t_data *data, char **tokens)
{
	int			i;
	t_toklst	*new_token_node;

	data->t_lst = (t_toklst **)malloc(sizeof(t_toklst *));
	if (!data->t_lst)
		ft_error(errno, strerror(errno));
	*data->t_lst = NULL;
	i = 0;
	while (tokens[i])
	{
		new_token_node = token_lstnew_node(tokens[i]);
		token_lstadd_back((*data).t_lst, new_token_node);
		i++;
	}
}

/**
 * @brief the lexer function
 * @param data pointer to the data struct
 */
void	lexer(t_data *data)
{
	data->tokens = input_to_token_array(data, data->input);
	token_array_to_list(data, data->tokens);
	return ;
}
