/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:14:56 by ohosnedl          #+#    #+#             */
/*   Updated: 2023/09/26 12:42:50 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int	put_ptr(uintptr_t num)
{
	char	*symbols;
	int		return_value;

	return_value = 0;
	symbols = "0123456789abcdef";
	if (num >= 16)
	{
		return_value += put_ptr(num / 16);
		return_value += put_ptr(num % 16);
	}
	else
		return_value += write(1, &symbols[num], 1);
	return (return_value);
}

int	print_pointer(unsigned long long ptr)
{
	int	return_value;

	return_value = 0;
	if (ptr == 0)
		return_value += write(1, "(nil)", 5);
	else
	{
		return_value += write(1, "0x", 2);
		return_value += put_ptr(ptr);
	}
	return (return_value);
}
