/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_digit_lower.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 13:14:57 by ohosnedl          #+#    #+#             */
/*   Updated: 2023/09/25 13:38:52 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_digit_lower(long n, int base)
{
	int		return_value;
	char	*symbols;

	return_value = 0;
	symbols = "0123456789abcdef";
	if (n < 0)
	{
		return_value += write(1, "-", 1);
		return_value += print_digit_lower(-n, base);
	}
	else if (n < base)
		return_value += print_char(symbols[n]);
	else
	{
		return_value += print_digit_lower(n / base, base);
		return_value += print_digit_lower(n % base, base);
	}
	return (return_value);
}
