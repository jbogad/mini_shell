/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:01:42 by clalopez          #+#    #+#             */
/*   Updated: 2025/01/17 10:30:23 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
/*#include <stdio.h>
int	main(void)
{
	char car = '7';

	if (ft_isdigit(car))
		printf("'%c'Si\n", car);
	else
		printf("'%c'No\n", car);

	return (0);
}*/