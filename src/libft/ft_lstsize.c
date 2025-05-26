/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:58:40 by clalopez          #+#    #+#             */
/*   Updated: 2025/01/24 12:16:17 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}

/*cc -Wall -Wextra -Werror -o test_lstsize ft_lstsize.c ft_lstnew.c
int main() {
	
	int a = 42;
    int b = 84;
    int c = 21;

    t_list *node1 = ft_lstnew(&a);
    t_list *node2 = ft_lstnew(&b);
    t_list *node3 = ft_lstnew(&c);

    node1->next = node2;
    node2->next = node3;

    printf("Tamaño de la lista: %d\n", ft_lstsize(node1));

    free(node1);
    free(node2);
    free(node3);

    return 0;
}*/
