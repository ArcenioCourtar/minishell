/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exp_split.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/11 15:15:57 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2024/01/11 15:15:57 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "libft.h"

/**
 * @brief Counts the number of words in a string
 * @param s The string to count the words in
 * @return The number of words in the string
 */
static size_t	word_counter(char const *s)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s && s[i])
	{
		if (!ft_iswhitespace(s[i]))
		{
			count++;
			while (!ft_iswhitespace(s[i]) && s[i])
				i++;
		}
		else
			i++;
	}
	return (count);
}

/**
 * @brief Inserts words delimited by whitespace into an array of strings
 * @param s The string to insert the words from
 * @param str The array of strings to insert the words into
 * @param w_count The number of words in the string
 * @return 1 on success, 0 on failure
 */
static int	insert_word(t_data *data, char const *s, char **str_arr, \
															size_t w_count)
{
	size_t	i;
	size_t	j;
	size_t	start;

	i = -1;
	j = 0;
	while (j < w_count)
	{
		if (!ft_iswhitespace(s[++i]))
		{
			start = i;
			while (!ft_iswhitespace(s[i]) && s[i] != '\0')
				i++;
			str_arr[j] = ft_substr(s, start, i - start);
			add_to_free_lst(data, str_arr[j]);
			if (str_arr[j] == 0)
				return (0);
			j++;
		}
	}
	str_arr[j] = NULL;
	return (1);
}

/**
 * @brief Splits a string into an array of strings
 * @param s The string to split
 * @return The array of strings
 */
static char	**ft_split_wspace(t_data *data, char const *s)
{
	char	**str_arr;
	size_t	word_count;

	word_count = word_counter(s);
	str_arr = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!str_arr)
		return (NULL);
	if (!insert_word(data, s, str_arr, word_count))
	{
		free_double_array(str_arr);
		return (NULL);
	}
	return (str_arr);
}

/**
 * @brief Splits a token into multiple tokens
 * @param data The program data struct
 * @param token The pointer to the token list
 */
void	split_expansion(t_data *data, t_toklst **token)
{
	char		**split_exp;
	int			i;
	t_toklst	*tmp_node;
	t_toklst	*tmp_token;

	split_exp = ft_split_wspace(data, (*token)->token);
	i = 0;
	(*token)->token = split_exp[i];
	(*token)->type = get_token_type(split_exp[i]);
	i++;
	tmp_token = (*token);
	while (split_exp[i])
	{
		tmp_node = token_lstnew_node(split_exp[i]);
		tmp_node->next = tmp_token->next;
		tmp_node->prev = tmp_token;
		tmp_token->next = tmp_node;
		tmp_token = tmp_token->next;
		i++;
	}
	free(split_exp);
}
