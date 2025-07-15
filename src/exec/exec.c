/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaboga-d <jaboga-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:04:51 by jaboga-d          #+#    #+#             */
/*   Updated: 2025/07/15 15:45:42 by jaboga-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	fill_cmd_args(t_token **tokens, t_shell *msh);
static void	free_cmd_args(t_shell *msh);
static void	execute_builtin(t_token **tokens, t_shell *msh);

/**
 * @brief Ejecuta un comando con sus argumentos.
 * @param tokens Array de tokens que representa el comando.
 * @param msh Estructura principal del shell.
 */
void	execute(t_token **tokens, t_shell *msh)
{
	if (!tokens || !tokens[0] || tokens[0]->type != TOKEN_WORD)
		return ;
	fill_cmd_args(tokens, msh);
	execute_builtin(tokens, msh);
}

/**
 * @brief Llena el array cmd_args con los valores de los tokens.
 * @param tokens Array de tokens de entrada.
 * @param msh Estructura principal del shell.
 */
static void	fill_cmd_args(t_token **tokens, t_shell *msh)
{
	int	i;

	i = 0;
	while (tokens[i])
		i++;
	msh->count_cmd_args = i;
	free_cmd_args(msh);
	msh->cmd_args = malloc(sizeof(char *) * (msh->count_cmd_args + 1));
	i = 0;
	while (tokens[i])
	{
		msh->cmd_args[i] = ft_strdup(tokens[i]->value);
		i++;
	}
	msh->cmd_args[i] = NULL;
}

/**
 * @brief Libera la memoria del array cmd_args anterior.
 * @param msh Estructura principal del shell.
 */
static void	free_cmd_args(t_shell *msh)
{
	int	i;

	if (msh->cmd_args)
	{
		i = 0;
		while (msh->cmd_args[i])
		{
			free(msh->cmd_args[i]);
			i++;
		}
		free(msh->cmd_args);
	}
}

/**
 * @brief Identifica y ejecuta el comando builtin correspondiente.
 * @param tokens Array de tokens con el comando.
 * @param msh Estructura principal del shell.
 */
static void	execute_builtin(t_token **tokens, t_shell *msh)
{
	if (ft_strncmp(tokens[0]->value, "pwd", ft_strlen("pwd")) == 0)
		ft_pwd();
	else if (ft_strncmp(tokens[0]->value, "echo", ft_strlen("echo")) == 0)
		ft_echo(tokens);
	else if (ft_strncmp(tokens[0]->value, "cd", ft_strlen("cd")) == 0)
		ft_cd(tokens);
	else if (ft_strncmp(tokens[0]->value, "export", ft_strlen("export")) == 0)
		ft_export(msh);
	else
		ft_printf("error\n", tokens[0]->value);
}
