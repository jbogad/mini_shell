/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:56:36 by clalopez          #+#    #+#             */
/*   Updated: 2025/01/24 15:23:26 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*next;

	if (!lst || !del)
		return ;
	current = *lst;
	while (current)
	{
		next = current->next;
		del(current->content);
		free(current);
		current = next;
	}
	*lst = NULL;
}
// cc -Wall -Wextra -Werror -o test_ft_lstclear  ft_lstclear.c ft_lstnew.c
/*void del(void *content)
{
	free(content);
}

int	main(void)
{
	t_list *list = ft_lstnew(malloc(sizeof(int)));
	*(int *)list->content = 42;

	t_list *node2 = ft_lstnew(malloc(sizeof(int)));
	*(int *)node2->content = 84;

	t_list *node3 = ft_lstnew(malloc(sizeof(int)));
	*(int *)node3->content = 126;

	list->next = node2;
	node2->next = node3;

	ft_lstclear(&list, del);

	if (list == NULL)
		printf("Lista vaciada\n");
}*/