/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 12:19:22 by jaboga-d          #+#    #+#             */
/*   Updated: 2025/09/09 14:56:00 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_valid_name(char *name)
{
	int	i;

	if (!name || !name[0] || ft_isdigit(name[0]))
		return (0);
	i = 0;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	update_existing_env(t_env *existing, char *value)
{
	free(existing->val_env);
	existing->val_env = ft_strdup(value);
}

static void	process_export_with_value(char *arg, t_shell *msh, char *equal)
{
	char	*name;
	char	*value;
	t_env	*existing;
	t_env	*new;

	name = ft_substr(arg, 0, equal - arg);
	value = ft_strdup(equal + 1);
	if (!name || !value)
	{
		free(name);
		free(value);
		return ;
	}
	existing = find_env(msh->env, name);
	if (existing)
		update_existing_env(existing, value);
	else
	{
		new = ft_lstnew_env(name, value, 1);
		if (new)
			ft_lstadd_back_env(&(msh->env), new);
	}
	free(name);
	free(value);
}

void	add_arg_to_env(char *arg, t_shell *msh)
{
	char	*equal;
	t_env	*new;

	if (!arg || !msh)
		return ;
	equal = ft_strchr(arg, '=');
	if (equal)
		process_export_with_value(arg, msh, equal);
	else
	{
		if (!find_env(msh->env, arg))
		{
			new = ft_lstnew_env(arg, "", 1);
			if (new)
				ft_lstadd_back_env(&(msh->env), new);
		}
	}
}
