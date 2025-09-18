/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:06:24 by jaboga-d          #+#    #+#             */
/*   Updated: 2025/09/17 15:18:16 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//(Claudio) Funcion para expandir las variables
static char	*expand_arg(char *arg, t_shell *msh)
{
	char	*value;

	if (!arg)
		return (ft_strdup(""));
	if (ft_strcmp(arg, "$?") == 0 || ft_strcmp(arg, "?") == 0)
		return (ft_itoa(msh->exit_status));
	if (arg[0] == '$')
	{
		value = get_env_value(msh->env, arg + 1);
		if (value)
			return (ft_strdup(value));
		else
			return (ft_strdup(""));
	}
	return (ft_strdup(arg));
}

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

void	expand_echo(t_token *token, t_shell *msh)
{
	char	*expanded;

	if (token->type != TOKEN_SIM_QUOTE)
	{
		expanded = expand_arg(token->value, msh);
		ft_printf("%s", expanded);
		free(expanded);
	}
	else
		ft_printf("%s", token->value);
}

void	ft_echo(t_token **tokens, t_shell *msh)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 1;
	while (tokens[i] && (tokens[i]->type == TOKEN_WORD
			|| tokens[i]->type == TOKEN_DOB_QUOTE
			|| tokens[i]->type == TOKEN_SIM_QUOTE)
		&& is_valid_n_option(tokens[i]->value))
	{
		new_line = 0;
		i++;
	}
	while (tokens[i] && (tokens[i]->type == TOKEN_WORD
			|| tokens[i]->type == TOKEN_DOB_QUOTE
			|| tokens[i]->type == TOKEN_SIM_QUOTE))
	{
		expand_echo(tokens[i], msh);
		if (tokens[i + 1])
			ft_printf(" ");
		i++;
	}
	if (new_line)
		ft_printf("\n");
}
