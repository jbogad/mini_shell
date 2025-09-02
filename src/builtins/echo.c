/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbogad <jbogad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:06:24 by jaboga-d          #+#    #+#             */
/*   Updated: 2025/09/02 15:47:38 by jbogad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
funcion para echo
acepta echo y echo -n, de norma imprime salto de linea
si no el siguiente token no es null, imprime un espacio para meter el siguiente
si new_line es uno, imprime salto de linea
*/

static int	is_valid_n_option(char *str)
{
	int	i;

	if (!str || str[0] != '-' || str[1] == '\0')
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_echo(t_token **tokens)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 1;
	while (tokens[i] && tokens[i]->type == TOKEN_WORD
		&& is_valid_n_option(tokens[i]->value))
	{
		new_line = 0;
		i++;
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
