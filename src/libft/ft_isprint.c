/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:24:28 by clalopez          #+#    #+#             */
/*   Updated: 2025/01/17 10:31:01 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}
/*#include <stdio.h>
int	main(void)
{
	char car = 'm';

	if (ft_isprint(car))
		printf("'%c'Si\n", car);
	else
		printf("'%c'No\n", car);

	return (0);
}*/