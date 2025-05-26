/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 12:48:48 by clalopez          #+#    #+#             */
/*   Updated: 2025/01/27 12:25:33 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	start;
	size_t	end;
	size_t	len;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	len = end - start;
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1 + start, len + 1);
	return (str);
}

// gcc -Wall -Wextra -Werror
//	-o test_strtrim ft_strtrim.c ft_strlen.c ft_strchr.c ft_strlcpy.c
/*int main(void)
{
	char *s1 = "Claudio";
	char *set = "Clado";
	char *result;

	result = ft_strtrim(s1, set);


	printf("Resultado: '%s'\n", result);


	return (0);
}*/