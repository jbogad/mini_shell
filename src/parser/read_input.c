/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudio <claudio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 11:45:09 by claudio           #+#    #+#             */
/*   Updated: 2025/05/27 12:52:10 by claudio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


/*Funcion para crear el input(minishell)
e ir añadiendo los comandos utilizados al historial
maneja el add_history tambien las flechas de ir hacia arriba
y hacia abajo*/

char	*read_input()
{
	char	*input;

	input = readline("minishell$ ");
	if (input && *input != '\0')
		add_history(input);
    ft_printf("Input: %s\n", input);
	return (input);
}
