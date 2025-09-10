/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 11:45:09 by claudio           #+#    #+#             */
/*   Updated: 2025/09/10 13:10:28 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * @brief Funcion para crear el input(minishell) e ir
 *  añadiendo los comandos utilizados al historial maneja
 *  el add_history tambien las flechas de ir hacia arriba y hacia abajo
 * @return Retorna el input que se va escribiendo en la linea
 */
char	*read_input(void)
{
	char	*input;
	char	*prompt;
	char	*tmp;
	char	*short_path;

	short_path = get_short_path();
	tmp = ft_strjoin(GREEN_BRIGHT, short_path);
	prompt = ft_strjoin(tmp, RESET);
	free(tmp);
	free(short_path);
	input = readline(prompt);
	free(prompt);
	if (input && *input != '\0')
		add_history(input);
	return (input);
}
