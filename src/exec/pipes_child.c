/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 10:00:00 by jaboga-d          #+#    #+#             */
/*   Updated: 2025/09/08 13:00:05 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0);
}

static void	execute_builtin_pipe(char *cmd, t_token **cmd_tokens, t_shell *msh)
{
	if (ft_strcmp(cmd, "echo") == 0)
		ft_echo(cmd_tokens, msh);
	else if (ft_strcmp(cmd, "cd") == 0)
		ft_cd(msh);
	else if (ft_strcmp(cmd, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmd, "export") == 0)
		ft_export(msh);
	else if (ft_strcmp(cmd, "unset") == 0)
		ft_unset(msh);
	else if (ft_strcmp(cmd, "env") == 0)
		ft_env(msh);
	else if (ft_strcmp(cmd, "exit") == 0)
		ft_exit(msh);
}

static void	execute_builtin_in_pipe(char **argv, t_token **cmd_tokens,
			t_pipe_data *data)
{
	execute_builtin_pipe(argv[0], cmd_tokens, data->msh);
	if (cmd_tokens)
		free(cmd_tokens);
	exit(0);
}

static void	execute_pipe_command(t_pipe_data *data)
{
	char	**argv;
	t_token	**cmd_tokens;

	cmd_tokens = get_cmd_tokens(data);
	argv = build_cmd(data->tokens, data->cmd_idx);
	if (argv && argv[0])
	{
		if (is_builtin(argv[0]))
			execute_builtin_in_pipe(argv, cmd_tokens, data);
		else if (execvp(argv[0], argv) == -1)
		{
			if (cmd_tokens)
				free(cmd_tokens);
			exit(1);
		}
	}
	if (cmd_tokens)
		free(cmd_tokens);
	exit(1);
}

void	process_pipe_child(t_pipe_data *data)
{
	t_token		**cmd_tokens;

	cmd_tokens = get_cmd_tokens(data);
	setup_child_pipes(data->cmd_idx, data->total, data->pipes);
	if (cmd_tokens && data->msh)
		set_redirections(cmd_tokens, data->msh, -1);
	if (cmd_tokens)
		free(cmd_tokens);
	execute_pipe_command(data);
}
