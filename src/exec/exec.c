/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaboga-d <jaboga-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:04:51 by jaboga-d          #+#    #+#             */
/*   Updated: 2025/06/02 14:41:39 by jaboga-d         ###   ########.fr       */
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

void	execute(t_token **tokens)
{
	if (!tokens || !tokens[0] || tokens[0]->type != TOKEN_WORD)
		return ;
	if (ft_strncmp(tokens[0]->value, "pwd", ft_strlen("pwd")) == 0)
		ft_pwd();
	else if (ft_strncmp(tokens[0]->value, "echo", ft_strlen("echo")) == 0)
		ft_echo(tokens);
	else if (ft_strncmp(tokens[0]->value, "cd", ft_strlen("cd")) == 0)
		ft_cd(tokens);
	else
		ft_printf("error\n", tokens[0]->value);
}
