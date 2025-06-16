/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:02:34 by clalopez          #+#    #+#             */
/*   Updated: 2025/06/16 15:13:11 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Cuenta cauntas variables de entorno hay
int	count_env(char **envp)
{
	int	count;

	count = 0;
	while (envp[count])
		count++;
	return (count);
}

// Inicializa la estructura y va copiando lo que hay a la izquierda
// del igual en el nombre del env y lo que hay a la derecha lo pega
// en el valor
t_env	*init_env(char **envp)
{
	int		count;
	t_env	*env;
	char	*equal_sign;
	int		i;

	count = count_env(envp);
	env = malloc(sizeof(t_env) * (count + 1));
	i = 0;
	while (envp[i])
	{
		equal_sign = ft_strchr(envp[i], '=');
		if (equal_sign)
		{
			env[i].name_env = ft_substr(envp[i], 0, equal_sign - envp[i]);
			env[i].val_env = ft_strdup(equal_sign + 1);
		}
		i++;
	}
	env[i].name_env = NULL;
	env[i].val_env = NULL;
	return (env);
}

// Compara con el env el nombre que se le ha pasado,
// y si existe devuelve su valor
char	*get_env_value(t_env *env, char *name)
{
	int	i;

	i = 0;
	while (env[i].name_env)
	{
		if (ft_strcmp(env[i].name_env, name) == 0)
			return (env[i].val_env);
		i++;
	}
	return (NULL);
}

//Esto coge y junta lo que hay antes del $ si hay algo con el valor expandido
// de la variable de entorno 
void	get_value_expanded(char *new_value, t_token **tokens, int i, char *env)
{
	char	*dollar;

	dollar = ft_strchr(tokens[i]->value, '$');
	new_value = ft_strjoin(ft_substr(tokens[i]->value, 0, dollar
				- tokens[i]->value), env);
	free(tokens[i]->value);
	tokens[i]->value = new_value;
}
