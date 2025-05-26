/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:17:00 by clalopez          #+#    #+#             */
/*   Updated: 2025/01/24 12:39:37 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	int	count;

	if (!lst)
		return (NULL);
	count = 0;
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
		count++;
	}
	return (lst);
}
//cc -Wall -Wextra -Werror -o test_ft_lstlast  ft_lstlast.c ft_lstnew.c
/*int main() {
    int a = 42;
    int b = 84;
    int c = 21;

    t_list *node1 = ft_lstnew(&a);
    t_list *node2 = ft_lstnew(&b);
    t_list *node3 = ft_lstnew(&c);

    node1->next = node2;
    node2->next = node3;

    t_list *last_node = ft_lstlast(node1);
    printf("Ultimo nodo: %d\n", *(int *)last_node->content);
}*/
