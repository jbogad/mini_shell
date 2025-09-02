/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbogad <jbogad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:06:27 by jaboga-d          #+#    #+#             */
/*   Updated: 2025/09/02 12:43:53 by jbogad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_env(t_shell *msh)
{
	t_env	*tmp;

	if (!msh)
		return ;
	msh->exit_status = 0;
	tmp = msh->env;
	while (tmp)
	{
		if (tmp->name_env && tmp->val_env)
		{
			write(1, tmp->name_env, ft_strlen(tmp->name_env));
			write(1, "=", 1);
			write(1, tmp->val_env, ft_strlen(tmp->val_env));
			write(1, "\n", 1);
		}
		tmp = tmp->next;
	}
}
