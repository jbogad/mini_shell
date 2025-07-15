/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_to_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaboga-d <jaboga-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 12:32:49 by jaboga-d          #+#    #+#             */
/*   Updated: 2025/07/15 13:02:35 by jaboga-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_free_list(t_env **list)
{
	t_env	*tmp;

	while (*list)
	{
		tmp = (*list)->next;
		ft_memfree((*list)->name_env);
		ft_memfree((*list)->val_env);
		ft_memfree((*list));
		*list = tmp;
	}
	*list = NULL;
}

void	ft_memfree(void *ptr)
{
	if (!ptr)
		return ;
	free(ptr);
	ptr = NULL;
}
