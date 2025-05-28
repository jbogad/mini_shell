/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaboga-d <jaboga-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:04:51 by jaboga-d          #+#    #+#             */
/*   Updated: 2025/05/28 20:23:32 by jaboga-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
logica principal (decide si es un comando interno o externo)
*/

/*
MANEJAR ERRORES
comprobar casuísticas para cada comando
me da error en pwdasd->arreglar
*/

void execute(t_token **tokens)
{
    if (!tokens || !tokens[0] || tokens[0]->type != TOKEN_WORD)
        return; // Manejo básico de errores

    if (ft_strncmp(tokens[0]->value, "pwd", ft_strlen("pwd")) == 0)//para comprobar el error de pwdcdasawe -> falla
        ft_pwd();
    else
        ft_printf("error\n", tokens[0]->value);
}