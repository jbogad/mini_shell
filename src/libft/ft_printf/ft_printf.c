/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbogad <jbogad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:02:57 by clalopez          #+#    #+#             */
/*   Updated: 2025/09/02 12:43:54 by jbogad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	formatter(va_list va, char *str, size_t *count)
{
	if (*str == 'c')
		print_char(va_arg(va, int), count);
	else if (*str == 's')
		print_string(va_arg(va, char *), count);
	else if (*str == 'p')
		print_pointer_void(va_arg(va, void *), count);
	else if (*str == 'd' || *str == 'i')
		print_number_decimal(va_arg(va, int), count);
	else if (*str == 'u')
		print_number_unsigned(va_arg(va, int), count);
	else if (*str == 'x')
		print_num_hex_minus(va_arg(va, int), count);
	else if (*str == 'X')
		print_num_hex_mayus(va_arg(va, int), count);
	else if (*str == '%')
		print_char('%', count);
}

int	ft_printf(char const *s, ...)
{
	va_list	va;
	size_t	count;

	count = 0;
	if (!s)
		return (0);
	va_start(va, s);
	while (*s)
	{
		if (*s == '%')
		{
			s++;
			formatter(va, (char *)s, &count);
			s++;
		}
		else
		{
			print_char(*s, &count);
			s++;
		}
	}
	va_end(va);
	return (count);
}

/* int main()
{
    char c = 'd';    
    ft_printf("Char con mi ft_printf: %c\n", c);
    printf("Char con printf: %c\n", c);

    char *str = "Hola Claudio daodkaodka 3810 ";
    ft_printf("\nString con mi ft_printf: %s\n", str);
    printf("String con printf: %s\n", str);
   
    void *ptr = "jve8jv9e";
    ft_printf("\nPuntero void con mi ft_printf: %p\n", ptr);
    printf("Puntero void con printf: %p\n", ptr);
   
    int num = 39;
    ft_printf("\nNumero con mi ft_printf: %d  %i\n", num, num);
    printf("Numero con printf: %d  %i\n", num, num);
   
    unsigned int u_num = 220393;
    ft_printf("\nNumero sin signo con mi ft_printf: %u\n", u_num);
    printf("Numero sin signo con printf: %u\n", u_num);
   
    int hex_num = 42;
    ft_printf("\nHexadecimal (minuscula) con mi ft_printf: %x\n", hex_num);
    printf("Hexadecimal (minuscula) con printf: %x\n", hex_num);
   
    ft_printf("\nHexadecimal (mayuscula) con mi ft_printf: %X\n", hex_num);
    printf("Hexadecimal (mayuscula) con printf: %X\n", hex_num);
   
    ft_printf("\nPorcentaje con mi ft_printf: %%\n");
    printf("Porcentaje con printf: %%\n");
   
    return 0;
} */