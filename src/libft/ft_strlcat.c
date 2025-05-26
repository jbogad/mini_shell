/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:47:55 by clalopez          #+#    #+#             */
/*   Updated: 2025/01/27 11:00:59 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	s_dst;
	size_t	s_src;

	s_dst = 0;
	s_src = 0;
	i = 0;
	while (s_dst < size && dst[s_dst] != '\0')
		s_dst++;
	while (src[s_src] != '\0')
		s_src++;
	if (s_dst >= size)
		return (s_src + size);
	while ((s_dst + i) < (size - 1) && src[i] != '\0')
	{
		dst[s_dst + i] = src[i];
		i++;
	}
	dst[s_dst + i] = '\0';
	return (s_dst + s_src);
}

/*int main()
{
	char dest[30] = "Hello, ";
	char *src = "Claudio123456789!";
	size_t size = 16;

	ft_strlcat(dest, src, size);

	printf("Resultao: %s\n", dest);

	return (0);
}*/