/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirects.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/18 15:34:10 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2023/07/18 15:34:10 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "parser.h"
#include "lexer.h"

int	redirect_count(t_data data)
{
	int		count;
	t_token	*tmp;

	count = 0;
	tmp = *(data.t_lst);
	while (tmp)
	{
		if (tmp->type == TOK_REDOUT || tmp->type == TOK_REDIN)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

void	create_redir_array(t_parser_data *p_data, t_data data)
{
	t_token	*tmp;
	int		i;

	tmp = *(data.t_lst);
	i = 0;
	while (tmp)
	{
		if (tmp->type == TOK_REDOUT || tmp->type == TOK_REDIN)
		{
			tmp = tmp->next;
			while (tmp && tmp->type == TOK_SPACE)
				tmp = tmp->next;
			if (!tmp)
				break ;
			if (tmp->type != TOK_NAME && tmp->type != TOK_DQUOTE && tmp->type != TOK_SQUOTE)
			{
				ft_error(1, "syntax\n");
				//should become error that gives prompt back and not exit
			}
			else
			{
				p_data->redirect_files[i] = tmp->token;
				i++;
			}
		}
		tmp = tmp->next;
	}
	p_data->redirect_files[i] = NULL;
}

void	redirects(t_data data)
{
	t_parser_data	p_data;
	int				redir_count;

	redir_count = redirect_count(data);
	p_data.redirect_files = (char **)malloc(sizeof(char *) * (redir_count + 1));
	create_redir_array(&p_data, data);
	//testing-----------------------------------------------------------------------
	ft_printf("count: %i\n", redir_count);
	int	i = 0;
	while (p_data.redirect_files[i])
	{
		ft_printf("%i: %s\n", i, p_data.redirect_files[i]);
		i++;
	}
}
