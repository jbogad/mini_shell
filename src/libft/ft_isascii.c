/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:12:21 by clalopez          #+#    #+#             */
/*   Updated: 2025/01/17 10:29:39 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}
/*#include <stdio.h>
int	main(void)
{
	char car = ',';

	if (ft_isascii(car))
		printf("'%c'Si\n", car);
	else
		printf("'%c'No\n", car);

	return (0);
}*/