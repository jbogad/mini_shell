/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:32:51 by jaboga-d          #+#    #+#             */
/*   Updated: 2025/09/19 11:32:26 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <sys/wait.h>

char	**create_argv_array(t_token **tokens)
{
	char	**argv;
	int		count;
	int		i;

	count = 0;
	while (tokens[count] && tokens[count]->type == TOKEN_WORD)
		count++;
	argv = malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return (NULL);
	i = 0;
	while (i < count)
	{
		argv[i] = ft_strdup(tokens[i]->value);
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

char	**create_env_array(t_env *env_list)
{
	char	**envp;
	char	*temp;
	int		count;
	t_env	*current;

	count = 0;
	current = env_list;
	while (current && ++count)
		current = current->next;
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	count = 0;
	current = env_list;
	while (current)
	{
		temp = ft_strjoin(current->name_env, "=");
		envp[count] = ft_strjoin(temp, current->val_env);
		free(temp);
		current = current->next;
		count++;
	}
	envp[count] = NULL;
	return (envp);
}

void	free_arrays(char **argv, char **envp)
{
	int	i;

	if (argv)
	{
		i = 0;
		while (argv[i])
			free(argv[i++]);
		free(argv);
	}
	if (envp)
	{
		i = 0;
		while (envp[i])
			free(envp[i++]);
		free(envp);
	}
}

char	*find_path(char *cmd, t_env *env)
{
	char	**paths;
	char	*temp;
	char	*full_path;
	int		i;

	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	paths = get_paths(env);
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		temp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(full_path, X_OK) == 0)
			return (free_arrays(paths, NULL), full_path);
		free(full_path);
	}
	return (free_arrays(paths, NULL), NULL);
}

void	execute_external_command(t_token **tokens, t_shell *msh)
{
	char	*cmd_path;
	pid_t	pid;
	int		status;

	cmd_path = get_command_path(tokens, msh);
	if (!cmd_path)
		return ;
	pid = fork();
	if (pid == 0)
		child_process(cmd_path, tokens, msh);
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		msh->exit_status = WEXITSTATUS(status);
	}
	else
		perror("fork");
	free(cmd_path);
}
