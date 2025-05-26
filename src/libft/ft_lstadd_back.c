/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:44:40 by clalopez          #+#    #+#             */
/*   Updated: 2025/01/24 14:36:15 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = new;
}
// cc -Wall -Wextra -Werror -o test_ft_lstadd_back  ft_lstadd_back.c ft_lstnew.c
/*int main()
{
    int a = 42;
    int b = 84;

    t_list *list = ft_lstnew(&a);
    t_list *node2 = ft_lstnew(&b);

    ft_lstadd_back(&list, node2);

    t_list *current = list;

    printf("Contenido del nodo: %d\n", *(int *)current->content);
    current = current->next;
}*/
