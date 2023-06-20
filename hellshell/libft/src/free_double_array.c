/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_double_array.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/15 15:07:07 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2023/02/15 15:07:24 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_double_array(char **d_arr)
{
	size_t	i;

	i = 0;
	if (!d_arr)
		return ;
	while (d_arr[i])
	{
		free(d_arr[i]);
		i++;
	}
	free(d_arr);
}
