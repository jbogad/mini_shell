/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 12:06:54 by clalopez          #+#    #+#             */
/*   Updated: 2025/09/07 12:01:59 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*dup;
	size_t	i;

	dup = malloc(n + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < n && s[i] != '\0')
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0'))
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	return (0);
}

void	free_env(t_env *env_list)
{
	t_env	*tmp;
	int		safety_counter;

	safety_counter = 0;
	while (env_list && safety_counter < 1000)
	{
		safety_counter++;
		tmp = env_list;
		env_list = env_list->next;
		if (tmp->name_env)
			free(tmp->name_env);
		if (tmp->val_env)
			free(tmp->val_env);
		free(tmp);
		if (!env_list)
			break ;
	}
}

void	free_tokens(t_token **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		free(tokens[i]->value);
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

int	get_shell_pid(void)
{
	int		fd[2];
	pid_t	pid;
	int		shell_pid;

	if (pipe(fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		exit(0);
	else
	{
		shell_pid = pid;
		wait(NULL);
		return (shell_pid);
	}
}
