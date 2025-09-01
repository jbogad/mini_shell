/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaboga-d <jaboga-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:05:31 by jaboga-d          #+#    #+#             */
/*   Updated: 2025/08/30 10:30:00 by jaboga-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	set_redirections(t_token **tokens, t_shell *msh, int hdoc_fd)
{
	char	*cmd_name;
	int		i;
	int		status;

	if (!tokens)
		return (1);
	cmd_name = find_command(tokens);
	status = 1;
	i = 0;
	while (tokens[i] && tokens[i]->type != TOKEN_PIPE && status == 1)
	{
		if (tokens[i]->type == TOKEN_REDIR_IN)
			status = set_infile(tokens, msh, cmd_name);
		else if (tokens[i]->type == TOKEN_HEREDOC && hdoc_fd != -1)
			set_child_hdoc(hdoc_fd, cmd_name);
		else if (tokens[i]->type == TOKEN_REDIR_OUT)
			status = set_outfile(tokens, msh);
		else if (tokens[i]->type == TOKEN_APPEND)
			status = set_append_outfile(tokens, msh);
		i++;
	}
	return (status);
}
