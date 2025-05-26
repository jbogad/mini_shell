/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:05:08 by clalopez          #+#    #+#             */
/*   Updated: 2025/01/24 12:06:04 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

/*cc -Wall -Wextra -Werror -o test_lstadd_front ft_lstadd_front.c ft_lstnew.c
int	main(void) {
	int value = 42;

	t_list *node = ft_lstnew(&value);

	int new_value = 84;
	t_list *new_node = ft_lstnew(&new_value);

	ft_lstadd_front(&node, new_node);

	printf("Contenido del primer nodo: %d\n", *(int *)node->content);
	printf("Contenido del segundo nodo: %d\n", *(int *)node->next->content);
}*/