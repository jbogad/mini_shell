/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaboga-d <jaboga-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:06:24 by jaboga-d          #+#    #+#             */
/*   Updated: 2025/06/02 14:33:41 by jaboga-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void ft_echo(t_token **tokens)
{
    int idx;
    int new_line;

    idx = 1;
    new_line = 1;
    if (tokens[idx] && tokens[idx]->type == TOKEN_WORD)
    {
        if (ft_strncmp(tokens[idx]->value, "-n", 3) == 0)
        {
            new_line = 0;
            idx++;
        }
    }
    while (tokens[idx] && tokens[idx]->type == TOKEN_WORD)
    {
        ft_printf("%s", tokens[idx]->value);
        if (tokens[idx + 1])
            ft_printf(" ");
        idx++;
    }
    if (new_line)
        ft_printf("\n");
}
