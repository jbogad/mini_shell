/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:24:00 by clalopez          #+#    #+#             */
/*   Updated: 2025/01/17 10:31:03 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int c)
{
	return (((c >= 65 && c <= 90) || (c >= 97 && c <= 122)) || (c >= 48
			&& c <= 57));
}

/*#include <stdio.h>
int	main(void)
{
	char car = '-';

	if (ft_isalnum(car))
		printf("'%c'Si\n", car);
	else
		printf("'%c'No\n", car);

	return (0);
}*/