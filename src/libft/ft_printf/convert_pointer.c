/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_pointer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:29:35 by clalopez          #+#    #+#             */
/*   Updated: 2025/02/21 10:29:41 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_pointer_void(void *pointer, size_t *count)
{
	static const char	*hex_digits;
	unsigned long		num;
	char				str[16];
	int					i;

	hex_digits = "0123456789abcdef";
	i = 0;
	if (pointer == NULL)
	{
		write(1, "(nil)", 5);
		*count += 5;
		return ;
	}
	num = (unsigned long)pointer;
	print_char('0', count);
	print_char('x', count);
	while (num)
	{
		str[i] = hex_digits[num % 16];
		num /= 16;
		i++;
	}
	while (i--)
		print_char(str[i], count);
}
