/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaboga-d <jaboga-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:25:47 by clalopez          #+#    #+#             */
/*   Updated: 2025/08/13 18:25:08 by jaboga-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
    PARTE DE JAVIER
    main inicia las variables de entorno que las guarda en una lista t_env
    con valor de la variable y nombre de la variable.
    Genera la shell
    extrae los tokerns en una lista t_token depende del tipo de token que sea
    trata los heredoc << pero antes de ejecutar
    mi parte de ejecutro donde busca el comando
    libera los tokens y la entrada en cada iteracion del bucle
*/

extern volatile sig_atomic_t	g_skip_next_readline;

/**
 * @brief Esto simplemente comprueba que solo se ejecute ./minishell
 * Y abre la minishell
 */
char	*gen_shell(int argc, char **argv)
{
    (void)argv;
    if (argc != 1)
    {
        ft_putstr_fd("Error\n", 2);
        exit(1);
    }
    return (read_input());
}

/*Main para probar que se genera la shell y que la call_signals
funcionan*/
/*Main para probar pwd y creo que funciona bien(javier)*/
int	main(int argc, char **argv, char **envp)
{
    char    *input;
    t_token **tokens_ext;
    t_shell msh;
    int     i;

    // Imprime el contenido de envp para depuración
    int z = 0;
    printf("[DEBUG] Contenido de envp al arrancar:\n");
    while (envp[z])
    {
        printf("envp[%d]: %s\n", z, envp[z]);
        z++;
    }
    printf("==============================\n");

    // Inicializar la estructura t_shell
    ft_memset(&msh, 0, sizeof(t_shell));
    msh.env = init_env(envp);
    msh.exit_status = 0;
    msh.cmd_args = NULL;
    msh.count_cmd_args = 0;
    msh.tokens = NULL;
    msh.parser = NULL;

    call_signals();

    while (1)
    {
        printf("[DEBUG] INICIO de bucle while\n");
        
        if (g_skip_next_readline)
        {
            printf("[DEBUG] Saltando readline\n");
            g_skip_next_readline = 0;
            continue;
        }

        printf("[DEBUG] Llamando gen_shell...\n");
        input = gen_shell(argc, argv);
        printf("[DEBUG] gen_shell retornó: %s\n", input ? input : "NULL");
        
        if (!input)
        {
            ft_printf("exit\n");
            clear_history();
            break ;
        }

        if (*input)
        {
            printf("[DEBUG] Input no vacío, procesando...\n");
            tokens_ext = extract_all_tokens(input);
            heredoc(msh.env, tokens_ext);

            if (!g_skip_next_readline && tokens_ext && tokens_ext[0])
            {
                if (has_pipes(tokens_ext))
                    execute_pipes(tokens_ext, &msh);
                else
                    execute(tokens_ext, &msh);
            }

            // Liberar tokens
            i = 0;
            while (tokens_ext && tokens_ext[i])
            {
                free(tokens_ext[i]->value);
                free(tokens_ext[i]);
                i++;
            }
            free(tokens_ext);
        }
        else
        {
            printf("[DEBUG] Input vacío\n");
        }
        
        free(input);
        printf("[DEBUG] FIN de iteración, volviendo al inicio\n");
    }
    
    printf("[DEBUG] Iniciando cleanup final\n");
    free_cmd_args(&msh);  // ← Descomenta y prueba
    printf("[DEBUG] cmd_args liberado, ahora liberando env\n");
    free_env(msh.env);
    printf("[DEBUG] Cleanup completado\n");
    return (0);
}