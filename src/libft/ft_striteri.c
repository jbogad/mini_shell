/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:04:43 by clalopez          #+#    #+#             */
/*   Updated: 2025/01/27 14:06:21 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}

/*void lower(unsigned int i, char *c)
{
    (void)i;
    if (*c >= 'A' && *c <= 'Z')
    {
        *c = *c + 32;
    }
}
//cc -Wall -Wextra -Werror -o test_striteri ft_striteri.c ft_strlen.c
int main(void)
{
    char str[] = "Hola Claudio";

    ft_striteri(str, lower);

    printf("%s\n", str);

    return 0;
}*/