/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaboga-d <jaboga-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:06:24 by jaboga-d          #+#    #+#             */
/*   Updated: 2025/06/03 11:50:41 by jaboga-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
funcion para echo
acepta echo y echo -n, de norma imprime salto de linea
si no el siguiente token no es null, imprime un espacio para meter el siguiente
si new_line es uno, imprime salto de linea
*/
void	ft_echo(t_token **tokens)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 1;
	if (tokens[i] && tokens[i]->type == TOKEN_WORD)
	{
		if (ft_strncmp(tokens[i]->value, "-n", 3) == 0)
		{
			new_line = 0;
			i++;
		}
	}
	while (tokens[i] && tokens[i]->type == TOKEN_WORD)
	{
		ft_printf("%s", tokens[i]->value);
		if (tokens[i + 1])
			ft_printf(" ");
		i++;
	}
	if (new_line)
		ft_printf("\n");
}
