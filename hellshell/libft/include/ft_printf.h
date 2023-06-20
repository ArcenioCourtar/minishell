/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/25 16:11:30 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2022/10/31 14:00:45 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

int		ft_printf(const char *s, ...);
int		print_argument(const char *s, int i, va_list ap);
int		ft_printnbr(long int n);
void	ft_printchar(char c);
int		ft_printstr(char *s);
int		print_hex(unsigned long long hex, char x);

#endif