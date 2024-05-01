/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 13:28:09 by ohosnedl          #+#    #+#             */
/*   Updated: 2023/09/11 15:17:52 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int	print_format(char format, va_list arg)
{
	int	return_value;

	return_value = 0;
	if (format == 'c')
		return_value += print_char(va_arg(arg, int));
	else if (format == 's')
		return_value += print_str(va_arg(arg, char *));
	else if (format == 'p')
		return_value += print_pointer(va_arg(arg, unsigned long long));
	else if (format == 'd' || format == 'i')
		return_value += print_digit_lower(va_arg(arg, int), 10);
	else if (format == 'u')
		return_value += print_digit_lower(va_arg(arg, unsigned int), 10);
	else if (format == 'x')
		return_value += print_digit_lower(va_arg(arg, unsigned int), 16);
	else if (format == 'X')
		return_value += print_digit_upper(va_arg(arg, unsigned int), 16);
	else if (format == '%')
		return_value += write(1, "%", 1);
	else
		return_value += write(1, &format, 1);
	return (return_value);
}

int	ft_printf(const char *format, ...)
{
	int		return_value;
	va_list	arg;

	va_start(arg, format);
	return_value = 0;
	while (*format)
	{
		if (*format == '%')
			return_value += print_format(*(++format), arg);
		else
			return_value += write(1, format, 1);
		++format;
	}
	va_end(arg);
	return (return_value);
}
