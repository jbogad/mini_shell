/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:23:52 by clalopez          #+#    #+#             */
/*   Updated: 2025/06/17 14:34:36 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*strjoin_and_free(char *s1, char *s2)
{
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (tmp);
}

void	concat_result(t_expand *e, t_env *env_list, char *value)
{
	if (value[e->i] == '$')
	{
		e->start = ++e->i;
		while (value[e->i] && (ft_isalnum(value[e->i]) || value[e->i] == '_'))
			e->i++;
		e->var = ft_substr(value, e->start, e->i - e->start);
		e->env = get_env_value(env_list, e->var);
		free(e->var);
		if (e->env)
		{
			e->tmp = ft_strjoin(e->result, e->env);
			free(e->result);
			e->result = e->tmp;
		}
	}
	else
	{
		e->start = e->i;
		while (value[e->i] && value[e->i] != '$')
			e->i++;
		e->tmp = ft_substr(value, e->start, e->i - e->start);
		e->result = strjoin_and_free(e->result, e->tmp);
	}
}

char	*expand_all_vars(t_env *env_list, char *value)
{
	t_expand	*e;
	char		*final;

	e = malloc(sizeof(t_expand));
	e->i = 0;
	e->result = ft_strdup("");
	while (value[e->i])
		concat_result(e, env_list, value);
	final = e->result;
	free(e);
	return (final);
}

// Esto expande las variables de env, de momento con los TOKENS_WORD
// y creo que funciona como en el bash
void	expand_env_values(t_env *env_list, t_token **tokens)
{
	int		i;
	char	*expanded;

	i = 0;
	while (tokens[i] != NULL)
	{
		if (tokens[i]->type == TOKEN_WORD || tokens[i]->type == TOKEN_DOB_QUOTE)
		{
			expanded = expand_all_vars(env_list, tokens[i]->value);
			free(tokens[i]->value);
			tokens[i]->value = expanded;
		}
		i++;
	}
}
