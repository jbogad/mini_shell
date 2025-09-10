/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:32:51 by jaboga-d          #+#    #+#             */
/*   Updated: 2025/09/10 14:25:14 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../minishell.h"
#include <sys/wait.h>

static char	**create_argv_array(t_token **tokens)
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

static char	**create_env_array(t_env *env_list)
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

static void	free_arrays(char **argv, char **envp)
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
	char	*path_env;
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
	while (env && ft_strcmp(env->name_env, "PATH") != 0)
		env = env->next;
	if (!env)
		return (NULL);
	path_env = env->val_env;
	paths = ft_split(path_env, ':');
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
	char	**envp;
	char	**argv;

	//printf("DEBUG: Trying to execute: %s\n", tokens[0]->value);
	cmd_path = find_path(tokens[0]->value, msh->env);
	if (!cmd_path)
	{
		ft_printf("minishell: %s: command not found\n", tokens[0]->value);
		msh->exit_status = 127;
		return ;
	}
	printf("DEBUG: Found path: %s\n", cmd_path);
	pid = fork();
	if (pid == 0)
	{
		printf("DEBUG: Child process starting...\n");
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (ft_strcmp(tokens[0]->value, "./minishell") == 0)
		{
			printf("DEBUG: Child - setting up terminal for minishell\n");
			close(STDIN_FILENO);
			open("/dev/tty", O_RDONLY);
		}
		else
		{
			printf("DEBUG: Child - ensuring stdin is connected\n");
			if (!isatty(STDIN_FILENO)) //fumadita del subject que verifica si el stdin es un terminal
			{
				close(STDIN_FILENO);
				open("/dev/tty", O_RDONLY); //aunque este redirigido, lo conecta a /dev/tty para que pueda leer
			}
		}
		envp = create_env_array(msh->env);
		argv = create_argv_array(tokens);
		printf("DEBUG: Child calling execve...\n");
		execve(cmd_path, argv, envp);
		printf("DEBUG: execve failed!\n");
		free_arrays(argv, envp);
		exit(127);
	}
	else if (pid > 0)
	{
		printf("DEBUG: Parent waiting for child %d\n", pid);
		waitpid(pid, &status, 0);
		printf("DEBUG: Child exited with status: %d\n", WEXITSTATUS(status));
		msh->exit_status = WEXITSTATUS(status);
	}
	else
		perror("fork");
	free(cmd_path);
}
