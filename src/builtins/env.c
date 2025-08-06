/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaboga-d <jaboga-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:06:27 by jaboga-d          #+#    #+#             */
/*   Updated: 2025/08/06 20:08:48 by jaboga-d         ###   ########.fr       */
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
		if (tmp->name_env && tmp->val_env && tmp->val_env[0] != '\0')
			ft_printf("%s=%s\n", tmp->name_env, tmp->val_env);
		tmp = tmp->next;
	}
}
