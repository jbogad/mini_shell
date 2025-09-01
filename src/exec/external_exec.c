/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbogad <jbogad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:32:51 by jaboga-d          #+#    #+#             */
/*   Updated: 2025/09/01 16:08:23 by jbogad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <sys/wait.h>

static void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
}

static char	*build_cmd_path(char **paths, char *cmd)
{
	char	*full_path;
	char	*temp;
	int		i;

	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(full_path, X_OK) == 0)
		{
			free_paths(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_paths(paths);
	return (NULL);
}

/**
 * @brief Busca comando en PATH y retorna ruta completa
 */
char	*find_path(char *cmd, t_env *env)
{
	char	*path_env;
	char	**paths;

	while (env && ft_strcmp(env->name_env, "PATH") != 0)
		env = env->next;
	if (!env)
		return (NULL);
	path_env = env->val_env;
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	return (build_cmd_path(paths, cmd));
}

static void	exec_child_process(char *cmd_path, t_shell *msh)
{
	execve(cmd_path, msh->cmd_args, NULL);
	perror("execve");
	exit(127);
}

/**
 * @brief Ejecuta comando externo
 */
void	execute_external_command(t_token **tokens, t_shell *msh)
{
	char	*cmd_path;
	pid_t	pid;
	int		status;

	cmd_path = find_path(tokens[0]->value, msh->env);
	if (!cmd_path)
	{
		ft_printf("bash: %s: command not found\n", tokens[0]->value);
		msh->exit_status = 127;
		return ;
	}
	pid = fork();
	if (pid == 0)
		exec_child_process(cmd_path, msh);
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		msh->exit_status = WEXITSTATUS(status);
	}
	else
		perror("fork");
	free(cmd_path);
}
