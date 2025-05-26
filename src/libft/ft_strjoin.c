/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 12:06:12 by clalopez          #+#    #+#             */
/*   Updated: 2025/01/27 12:10:34 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	total_length;

	total_length = 0;
	j = 0;
	i = 0;
	if (!s1 || !s2)
		return (NULL);
	while (s1[total_length])
		total_length++;
	while (s2[j++])
		total_length++;
	str = (char *)malloc(total_length + 1);
	if (!str)
		return (NULL);
	while (*s1)
		str[i++] = *s1++;
	while (*s2)
		str[i++] = *s2++;
	str[i] = '\0';
	return (str);
}

/*int	main(void)
{
	char *s1 = "Hola ";
	char *s2 = "Claudio";
	char *result;

	result = ft_strjoin(s1, s2);

	printf("Resultado: %s\n", result);

	return (0);
}*/