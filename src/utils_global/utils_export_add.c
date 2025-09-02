/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export_add.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbogad <jbogad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 16:00:00 by jaboga-d          #+#    #+#             */
/*   Updated: 2025/09/02 14:20:26 by jbogad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	add_env(t_env **env_list, char *name, char *value)
{
	t_env	*existing;
	t_env	*new;

	if (!env_list || !name)
		return ;
	existing = find_env(*env_list, name);
	if (existing)
	{
		free(existing->val_env);
		if (value)
			existing->val_env = ft_strdup(value);
		else
			existing->val_env = ft_strdup("");
		return ;
	}
	new = ft_lstnew_env(name, value, 1);
	if (new)
		ft_lstadd_back_env(env_list, new);
}
