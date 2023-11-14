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
#include "parser.h"
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
	int			i;
	t_toklst	*tmp;

	i = 0;
	tmp = *dat.t_lst;
	while (tmp)
	{
		ft_printf("%i: '%s'\r\e[27Ctype: %i\n", i, tmp->token, \
		tmp->type);
		tmp = tmp->next;
		i++;
	}
}

void	printf_cmd_table(t_cmdlst **cmd_table_head)
{
	t_cmdlst	*tmp;
	int			i;
	int			j;

	i = 0;
	tmp = *(cmd_table_head);
	ft_printf("--First node--------------------------------\n");
	while (tmp)
	{
		ft_printf("[%i]\t type: %i\n", i, tmp->type);
		ft_printf("argv: \r\e[15C");
		j = 0;
		while (tmp->argv[j])
		{
			if (tmp->argv[j + 1])
				ft_printf("%s, ", tmp->argv[j]);
			else
				ft_printf("%s", tmp->argv[j]);
			j++;
		}
		ft_printf("\n");
		ft_printf("redirects: \r\e[15C");
		j = 0;
		if (tmp->redirect)
		{
			while (tmp->redirect[j].name)
			{
				if (tmp->redirect[j + 1].name)
					ft_printf("%s [%i], ", tmp->redirect[j].name, tmp->redirect[j].type);
				else
					ft_printf("%s [%i]", tmp->redirect[j].name, tmp->redirect[j].type);
				j++;
			}
		}
		tmp = tmp->next;
		if (tmp)
			ft_printf("\n\n||Pipe||||||||||||||||||||||||||\n\n");
		else
			ft_printf("\n--End of list------------------------\n");
		i++;
	}
}
