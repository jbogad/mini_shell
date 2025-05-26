/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:53:40 by clalopez          #+#    #+#             */
/*   Updated: 2025/01/27 11:58:21 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*str;

	str = malloc(nmemb * size);
	if (str == NULL)
		return (str);
	ft_memset(str, 0, nmemb * size);
	return (str);
}
/*gcc -Wall -Wextra -Werror -o test_calloc ft_calloc.c ft_memset.c
int main()
{
	int size = 5;
	int nmemb = sizeof(int);
	int *arr = ft_calloc(nmemb, size);

	int i = 0;
	
	while (i < size)
    {
        printf("arr[%d] = %d\n", i, arr[i]);
        i++;
    }
	return 0;
}*/