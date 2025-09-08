/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:04:51 by jaboga-d          #+#    #+#             */
/*   Updated: 2025/09/08 14:55:36 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	fill_cmd_args(t_token **tokens, t_shell *msh);
void		free_cmd_args(t_shell *msh);
static void	execute_builtin(t_token **tokens, t_shell *msh);

int	first_env_var(t_token **tokens, t_shell *msh)
{
	char	*name_var;
	char	*expanded;
	int		i;

	i = 0;
	if (!tokens || !tokens[0])
		return (0);
	name_var = tokens[0]->value;
	if (ft_strcmp(name_var, "$$") == 0)
	{
		printf("%d: command not found\n", msh->shell_pid);
		return (1);
	}
	if (ft_strcmp(name_var, "$?") == 0)
	{
		printf("%d: command not found\n", msh->exit_status);
		return (1);
	}
	if (name_var[0] == '$')
	{
		expanded = expand_all_vars(msh->env, name_var);
		if (!expanded)
			return (1);
		while (expanded[i])
		{
			if (expanded[i] == '/')
			{
				printf("minishell: %s: Is a directory\n", expanded);
				free(expanded);
				return (1);
			}
			i++;
		}
		free(tokens[0]->value);
		tokens[0]->value = expanded;
		return (0);
	}
	return (0);
}

/**
 * @brief Ejecuta un comando con sus argumentos y redirecciones.
 * @param tokens Array de tokens que representa el comando.
 * @param msh Estructura principal del shell.
 */
void	execute(t_token **tokens, t_shell *msh)
{
	int	stdin_backup;
	int	stdout_backup;
	int	status;

	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	if (!tokens || !tokens[0] || (tokens[0]->type != TOKEN_WORD
			&& tokens[0]->type != TOKEN_DOB_QUOTE
			&& tokens[0]->type != TOKEN_SIM_QUOTE))
		return ;
	if (tokens[0]->heredoc_fd != -1)
	{
		dup2(tokens[0]->heredoc_fd, STDIN_FILENO);
		close(tokens[0]->heredoc_fd);
	}
	status = set_redirections(tokens, msh, -1);
	if (status != 1)
		msh->exit_status = 1;
	else
	{
		if (first_env_var(tokens, msh) == 1)
			msh->exit_status = 127;
		else
		{
			expand_env_values(msh->env, tokens);
			fill_cmd_args(tokens, msh);
			execute_builtin(tokens, msh);
		}
	}
	if (dup2(stdin_backup, STDIN_FILENO) == -1)
		perror("dup2 stdin");
	if (dup2(stdout_backup, STDOUT_FILENO) == -1)
		perror("dup2 stdout");
	close(stdin_backup);
	close(stdout_backup);
}

static void	fill_cmd_args(t_token **tokens, t_shell *msh)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (!msh)
		return ;
	free_cmd_args(msh);
	if (!tokens || !tokens[0])
		return ;
	while (tokens[count] && tokens[count]->type == TOKEN_WORD)
		count++;
	if (count == 0)
		return ;
	msh->cmd_args = ft_calloc(count + 1, sizeof(char *));
	msh->count_cmd_args = count;
	while (i < count)
	{
		msh->cmd_args[i] = ft_strdup(tokens[i]->value);
		i++;
	}
}

void	free_cmd_args(t_shell *msh)
{
	int	i;

	if (!msh || !msh->cmd_args)
		return ;
	i = 0;
	while (i < msh->count_cmd_args)
	{
		free(msh->cmd_args[i]);
		msh->cmd_args[i] = NULL;
		i++;
	}
	free(msh->cmd_args);
	msh->cmd_args = NULL;
	msh->count_cmd_args = 0;
}

/**
 * @brief Identifica y ejecuta el comando builtin correspondiente.
 * @param tokens Array de tokens con el comando.
 * @param msh Estructura principal del shell.
 */
static void	execute_builtin(t_token **tokens, t_shell *msh)
{
	if (ft_strcmp(tokens[0]->value, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(tokens[0]->value, "echo") == 0)
		ft_echo(tokens, msh);
	else if (ft_strcmp(tokens[0]->value, "export") == 0)
		ft_export(msh);
	else if (ft_strcmp(tokens[0]->value, "exit") == 0)
		ft_exit(msh);
	else if (ft_strcmp(tokens[0]->value, "env") == 0)
		ft_env(msh);
	else if (ft_strcmp(tokens[0]->value, "unset") == 0)
		ft_unset(msh);
	else if (ft_strcmp(tokens[0]->value, "cd") == 0)
		ft_cd(msh);
	else
		execute_external_command(tokens, msh);
}
