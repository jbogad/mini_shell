/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_output.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaboga-d <jaboga-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 10:30:00 by jaboga-d          #+#    #+#             */
/*   Updated: 2025/08/30 10:30:00 by jaboga-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	open_output_file(char *file_name, int flags)
{
	int	fd;

	fd = open(file_name, flags, 0644);
	if (fd < 0)
	{
		perror(file_name);
		return (-1);
	}
	return (fd);
}

static int	setup_output_redirect(int fd, char *file_name)
{
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror(file_name);
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

static int	handle_output_file(t_token *file_token, t_shell *msh, int flags)
{
	char	*file_name;
	int		fd;

	file_name = expand_all_vars(msh->env, file_token->value);
	if (!file_name || ft_strchr(file_name, ' ') != NULL)
	{
		if (file_name)
			free(file_name);
		return (handle_ambiguous_redirect(file_token->value));
	}
	fd = open_output_file(file_name, flags);
	if (fd < 0)
	{
		free(file_name);
		return (0);
	}
	if (!setup_output_redirect(fd, file_name))
	{
		free(file_name);
		return (0);
	}
	free(file_name);
	return (1);
}

int	set_outfile(t_token **tokens, t_shell *msh)
{
	t_token	*file_token;

	file_token = find_redirection_file(tokens, TOKEN_REDIR_OUT);
	if (!file_token)
		return (1);
	return (handle_output_file(file_token, msh, O_RDWR | O_CREAT | O_TRUNC));
}

int	set_append_outfile(t_token **tokens, t_shell *msh)
{
	t_token	*file_token;

	file_token = find_redirection_file(tokens, TOKEN_APPEND);
	if (!file_token)
		return (1);
	return (handle_output_file(file_token, msh, O_RDWR | O_CREAT | O_APPEND));
}
