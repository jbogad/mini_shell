/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudio <claudio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:25:47 by clalopez          #+#    #+#             */
/*   Updated: 2025/05/27 15:30:31 by claudio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*Funcion para comprobar que solo se ejcuta el ejecutable
y generar la shell con el read_input*/
char *gen_shell(int argc, char **argv)
{
    (void)argv;
    if (argc != 1)
    {
        ft_putstr_fd("Error\n", 2);
        exit(1);
    }
    return read_input();
}
/*Main para probar que se genera la shell y que la call_signals
funcionan*/
int main(int argc, char **argv)
{
    char *input;
    call_signals();
    while (1)
    {
        input = gen_shell(argc, argv);
        if (!input)
            break;
        free(input);
    }
    return 0;
}
