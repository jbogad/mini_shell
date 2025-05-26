/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:09:03 by clalopez          #+#    #+#             */
/*   Updated: 2025/02/26 10:41:34 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

void	print_char(char c, size_t *count);
void	print_string(char *str, size_t *count);
void	print_pointer_void(void *pointer, size_t *count);
void	print_number_decimal(int n, size_t *count);
void	print_number_unsigned(unsigned int n, size_t *count);
void	print_num_hex_mayus(int n, size_t *count);
void	print_num_hex_minus(int n, size_t *count);
void	formatter(va_list va, char *str, size_t *count);
int		ft_printf(char const *s, ...);

#endif