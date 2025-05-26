/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:24:00 by clalopez          #+#    #+#             */
/*   Updated: 2025/01/27 12:09:51 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	i;
	size_t	str_len;

	str_len = 0;
	i = 0;
	if (!s)
		return (NULL);
	while (s[str_len])
		str_len++;
	if (start >= str_len)
		len = 0;
	else if (len > str_len - start)
		len = str_len - start;
	substring = (char *)malloc(len + 1);
	if (!substring)
		return (NULL);
	while (i < len && s[start + i])
	{
		substring[i] = s[start + i];
		i++;
	}
	substring[i] = '\0';
	return (substring);
}

/*int main()
{
	char *str = "Hola, claudio!";
	char *substr = ft_substr(str, 6, 6);

	printf("Substring: %s\n", substr);


	return (0);
}*/