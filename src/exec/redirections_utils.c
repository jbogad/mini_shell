/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaboga-d <jaboga-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 10:30:00 by jaboga-d          #+#    #+#             */
/*   Updated: 2025/08/30 10:30:00 by jaboga-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_builtin_redir(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	handle_ambiguous_redirect(char *filename)
{
	write(2, filename, ft_strlen(filename));
	write(2, ": ambiguous redirect\n", 21);
	return (0);
}

char	*find_command(t_token **tokens)
{
	int	i;

	if (!tokens)
		return (NULL);
	i = 0;
	while (tokens[i])
	{
		if (tokens[i]->type == TOKEN_WORD)
			return (tokens[i]->value);
		i++;
	}
	return (NULL);
}

t_token	*find_redirection_file(t_token **tokens, t_token_type redir_type)
{
	int	i;

	if (!tokens)
		return (NULL);
	i = 0;
	while (tokens[i])
	{
		if (tokens[i]->type == redir_type && tokens[i + 1])
			return (tokens[i + 1]);
		i++;
	}
	return (NULL);
}

void	set_child_hdoc(int hdoc_fd, char *cmd_name)
{
	if (!is_builtin_redir(cmd_name))
	{
		if (dup2(hdoc_fd, STDIN_FILENO) < 0)
			perror("dup2 heredoc");
	}
	close(hdoc_fd);
}
