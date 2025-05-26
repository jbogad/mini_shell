/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:05:33 by clalopez          #+#    #+#             */
/*   Updated: 2025/01/27 14:01:59 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*result;

	result = (char *)malloc((ft_strlen(s) + 1));
	i = 0;
	if (!result)
		return (NULL);
	while (s[i] != '\0')
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}

/*char lower(unsigned int i, char c)
{
	(void)i;
	if (c >= 'A' && c <= 'Z')
	{
		c = c + 32;
	}
	return c;
}
//cc -Wall -Wextra -Werror -o test_strmapi ft_strmapi.c ft_strlen.c
int main(void)
{
	char str[] = "HOLA CLAUDIO";
	char *result = ft_strmapi(str, lower);

	printf("%s\n", result);
}*/