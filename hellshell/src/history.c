/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   history.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/20 15:54:01 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2023/06/20 17:41:19 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static t_hislst	*new_history_node(char *input)
{
	t_hislst	*new_node;

	new_node = (t_hislst *)malloc(sizeof(t_hislst));
	if (!new_node)
		ft_error(errno, strerror(errno));
	new_node->command = input;
	new_node->next = NULL;
	new_node->n = 0;
	return (new_node);
}

static t_hislst	*history_lstlast(t_hislst *h_lst)
{
	if (!h_lst)
		return (NULL);
	else if (!h_lst->next)
		return (h_lst);
	else
		while (h_lst->next)
			h_lst = h_lst->next;
	return (h_lst);
}

static void	history_lstadd_back(t_hislst **h_lst, t_hislst *new)
{
	t_hislst	*tmp;

	if (!*h_lst)
	{
		*h_lst = new;
		return ;
	}
	else
	{
		tmp = history_lstlast(*h_lst);
		tmp->next = new;
	}
}

void	add_to_history_list(t_hislst **history_list, char *input)
{
	static int	i = 1;
	t_hislst	*node_to_add;

	node_to_add = new_history_node(input);
	node_to_add->n = i;
	i++;
	history_lstadd_back(history_list, node_to_add);
}

void	print_history_list(t_hislst **history_list)
{
	t_hislst	*tmp;

	tmp = *history_list;
	while (tmp)
	{
		ft_printf("    %i  %s\n", tmp->n, tmp->command);
		tmp = tmp->next;
	}
}

t_hislst	**init_history_list(void)
{
	t_hislst	**new_hlst;

	new_hlst = (t_hislst **)malloc(sizeof(t_hislst *));
	if (!new_hlst)
		ft_error(errno, strerror(errno));
	*new_hlst = NULL;
	return (new_hlst);
}
