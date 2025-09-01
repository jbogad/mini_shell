/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_input.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaboga-d <jaboga-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 10:30:00 by jaboga-d          #+#    #+#             */
/*   Updated: 2025/08/30 10:30:00 by jaboga-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	open_input_file(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		perror(file_name);
		return (-1);
	}
	return (fd);
}

static int	setup_input_redirect(int fd, char *file_name)
{
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror(file_name);
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

int	set_infile(t_token **tokens, t_shell *msh, char *cmd_name)
{
	char	*file_name;
	int		fd;
	t_token	*file_token;

	if (is_builtin_redir(cmd_name))
		return (1);
	file_token = find_redirection_file(tokens, TOKEN_REDIR_IN);
	if (!file_token)
		return (1);
	file_name = expand_all_vars(msh->env, file_token->value);
	if (!file_name || ft_strchr(file_name, ' ') != NULL)
	{
		if (file_name)
			free(file_name);
		return (handle_ambiguous_redirect(file_token->value));
	}
	fd = open_input_file(file_name);
	if (fd < 0)
	{
		free(file_name);
		return (0);
	}
	if (!setup_input_redirect(fd, file_name))
	{
		free(file_name);
		return (0);
	}
	free(file_name);
	return (1);
}
