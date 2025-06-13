/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 11:45:09 by claudio           #+#    #+#             */
/*   Updated: 2025/06/13 15:13:48 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*Funcion para crear el input(minishell)
e ir añadiendo los comandos utilizados al historial
maneja el add_history tambien las flechas de ir hacia arriba
y hacia abajo*/

char	*read_input(void)
{
	char	*input;
	char	*prompt;
	char	*tmp;

	tmp = ft_strjoin(RED_BRIGHT, get_short_path());
	prompt = ft_strjoin(tmp, RESET);
	free(tmp);
	if (!prompt)
		return (NULL);
	input = readline(prompt);
	free(prompt);
	if (input && *input != '\0')
		add_history(input);
	return (input);
}
