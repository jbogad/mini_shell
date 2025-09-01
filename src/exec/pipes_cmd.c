/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbogad <jbogad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 10:00:00 by jaboga-d          #+#    #+#             */
/*   Updated: 2025/08/31 12:37:37 by jbogad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	find_cmd_start(t_token **tokens, int cmd_idx)
{
	int	i;
	int	pipes_passed;

	i = 0;
	pipes_passed = 0;
	while (tokens[i] && pipes_passed < cmd_idx)
	{
		if (tokens[i]->type == TOKEN_PIPE)
			pipes_passed++;
		i++;
	}
	return (i);
}

static int	count_cmd_tokens(t_token **tokens, int start)
{
	int	j;

	j = start;
	while (tokens[j] && tokens[j]->type != TOKEN_PIPE)
		j++;
	return (j - start);
}

char	**build_cmd(t_token **tokens, int cmd_idx)
{
	char	**argv;
	int		i;
	int		j;
	int		cmd_length;

	i = find_cmd_start(tokens, cmd_idx);
	cmd_length = count_cmd_tokens(tokens, i);
	argv = malloc(sizeof(char *) * (cmd_length + 1));
	if (!argv)
		return (NULL);
	j = 0;
	while (tokens[i] && tokens[i]->type != TOKEN_PIPE)
		argv[j++] = ft_strdup(tokens[i++]->value);
	argv[j] = NULL;
	return (argv);
}
