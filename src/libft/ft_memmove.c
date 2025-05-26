/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:25:24 by clalopez          #+#    #+#             */
/*   Updated: 2025/01/27 10:44:20 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*u_dest;
	unsigned char	*u_src;

	if (!dest && !src)
		return (NULL);
	u_dest = dest;
	u_src = (unsigned char *)src;
	if (u_dest < u_src)
	{
		while (n--)
			*u_dest++ = *u_src++;
	}
	else
	{
		u_dest += n;
		u_src += n;
		while (n--)
			*(--u_dest) = *(--u_src);
	}
	return (dest);
}

/*int main(void)
{
    char src[] = "abcdef";
	char dest[] = "cddef";

    ft_memmove(dest, src, 10);
    printf("Resultado: %s\n", dest);

    return 0;
}*/
