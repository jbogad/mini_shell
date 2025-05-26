/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 15:28:52 by clalopez          #+#    #+#             */
/*   Updated: 2025/01/22 11:13:52 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	return ((c >= 65 && c <= 90) || (c >= 97 && c <= 122));
}
/*#include <stdio.h>
int	main(void)
{
	char car = 'A';

	if (ft_isalpha(car))
		printf("'%c'Si\n", car);
	else
		printf("'%c'No\n", car);

	return (0);
}*/