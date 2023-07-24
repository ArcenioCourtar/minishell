/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   testing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/28 16:39:15 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2023/06/28 16:39:15 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "lexer.h"

void	print_token_array(t_data dat)
{
	int	i;

	i = 0;
	while (dat.tokens[i])
	{
		ft_printf("%i: %s\n", i, dat.tokens[i]);
		i++;
	}
}

void	print_token_list(t_data dat)
{
	int		i;

	i = 0;
	while ((*dat.t_lst))
	{
		ft_printf("%i:\t%s\r\e[27Ctype: %i\n", i, (*dat.t_lst)->token, (*dat.t_lst)->type);
		(*dat.t_lst) = (*dat.t_lst)->next;
		i++;
	}
}

void	printf_cmd_table(t_parser_data *p_data)
{
	t_cmd	*tmp;
	int		i;
	int		j;

	i = 0;
	tmp = *(p_data->cmd_table);
	while (tmp)
	{
		ft_printf("[%i]\ncmd:\t%s\nargs:\t", i, tmp->command);
		j = 0;
		while (tmp->argv[j])
		{
			ft_printf("%s", tmp->argv[j]);
			j++;
			if (tmp->argv[j])
				ft_printf(", ");
			else
				ft_printf("\n");
		}
		tmp = tmp->next;
		i++;
	}
}
