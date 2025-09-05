/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:25:47 by clalopez          #+#    #+#             */
/*   Updated: 2025/09/05 11:22:29 by clalopez         ###   ########.fr       */
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
//fumadita para el shell level
static void	increment_shlvl(t_env **env_list)
{
	t_env	*shlvl_node;
	int		current_level;
	char	*new_level_str;

	shlvl_node = *env_list;
	while (shlvl_node && ft_strcmp(shlvl_node->name_env, "SHLVL") != 0)
		shlvl_node = shlvl_node->next;
	if (shlvl_node)
	{
		current_level = ft_atoi(shlvl_node->val_env);
		free(shlvl_node->val_env);
		new_level_str = ft_itoa(current_level + 1);
		shlvl_node->val_env = new_level_str;
	}
	else
	{
		new_level_str = ft_strdup("1");
		shlvl_node = ft_lstnew_env("SHLVL", new_level_str, 1);
		ft_lstadd_back_env(env_list, shlvl_node);
		free(new_level_str);
	}
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

    // Inicializar la estructura t_shell
    ft_memset(&msh, 0, sizeof(t_shell));
    msh.env = init_env(envp);
    increment_shlvl(&msh.env);
    msh.exit_status = 0;
    msh.cmd_args = NULL;
    msh.count_cmd_args = 0;
    msh.tokens = NULL;
    msh.parser = NULL;

    call_signals();

    while (1)
    {
        if (g_skip_next_readline)
        {
            g_skip_next_readline = 0;
            continue;
        }

        input = gen_shell(argc, argv);
        if (!input)
        {
            ft_printf("exit\n");
            clear_history();
            break ;
        }

        if (*input)
        {
            tokens_ext = extract_all_tokens(input);
            heredoc(msh.env, tokens_ext);
            if (!g_skip_next_readline && tokens_ext && tokens_ext[0])
            {
                int pipe_check = has_pipes(tokens_ext);
                if (pipe_check == -1)
                {
                    // Error de sintaxis, no ejecutar nada
                }
                else if (pipe_check == 1)
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
        
        free(input);
    }
    
    free_cmd_args(&msh);
    free_env(msh.env);
    return (0);
}
