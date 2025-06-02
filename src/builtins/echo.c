/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaboga-d <jaboga-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:06:24 by jaboga-d          #+#    #+#             */
/*   Updated: 2025/06/02 14:45:51 by jaboga-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_echo(t_token **tokens)
{
	int	index;
	int	new_line;

	index = 1;
	new_line = 1;
	if (tokens[index] && tokens[index]->type == TOKEN_WORD)
	{
		if (ft_strncmp(tokens[index]->value, "-n", 3) == 0)
		{
			new_line = 0;
			index++;
		}
	}
	while (tokens[index] && tokens[index]->type == TOKEN_WORD)
	{
		ft_printf("%s", tokens[index]->value);
		if (tokens[index + 1])
			ft_printf(" ");
		index++;
	}
	if (new_line)
		ft_printf("\n");
}
