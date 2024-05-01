/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 13:15:57 by ohosnedl          #+#    #+#             */
/*   Updated: 2023/09/11 15:47:36 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdint.h>

int	ft_printf(const char *format, ...);
int	print_char(int c);
int	print_digit_lower(long n, int base);
int	print_digit_upper(long n, int base);
int	print_str(char *s);
int	print_pointer(unsigned long long ptr);

#endif