/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:02:34 by clalopez          #+#    #+#             */
/*   Updated: 2025/09/16 12:27:37 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * @brief Cuenta el número de variables de entorno hay.
 * @param envp Array con las variables de entorno.
 * @return Número total de variables en `envp`.
 */
int	count_env(char **envp)
{
	int	count;

	count = 0;
	while (envp[count])
		count++;
	return (count);
}

/**
 * @brief Inicializa la lista de variables de entorno.
 * Recibe el array de cadenas `envp` y crea un arreglo
 * de estructuras `t_env` separando el nombre y valor de cada variable.
 * @param envp Arreglo de cadenas con las variables de entorno en formato
 * "NOMBRE=VALOR".
 * @return Arreglo de estructuras `t_env` con los nombres y valores
 * separados, terminado en NULL.
 */

void	add_env_node(char *name, char *value, t_env **env_list)
{
	t_env	*new_node;

	new_node = ft_lstnew_env(name, value, 1);
	if (new_node)
	{
		if (!*env_list)
			*env_list = new_node;
		else
			ft_lstadd_back_env(env_list, new_node);
	}
}

t_env	*init_env(char **envp)
{
	t_env	*env_list;
	char	*equal_sign;
	int		i;
	char	*name;
	char	*value;

	env_list = NULL;
	i = 0;
	while (envp[i])
	{
		equal_sign = ft_strchr(envp[i], '=');
		if (equal_sign)
		{
			name = ft_substr(envp[i], 0, equal_sign - envp[i]);
			value = ft_strdup(equal_sign + 1);
			add_env_node(name, value, &env_list);
			free(name);
			free(value);
		}
		i++;
	}
	return (env_list);
}

/**
 * @brief Obtiene el valor de una variable de entorno por su nombre.
 * Busca en la lista `env` la variable cuyo nombre coincida con `name`
 * y devuelve su valor asociado. Si no se encuentra, devuelve NULL.
 * @param env Arreglo de variables de entorno (t_env).
 * @param name Nombre de la variable a buscar.
 * @return Valor de la variable si se encuentra, NULL en caso contrario.
 */
char	*get_env_value(t_env *env, char *name)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name_env, name) == 0)
			return (tmp->val_env);
		tmp = tmp->next;
	}
	return (NULL);
}

/**
 * @brief Reemplaza el primer '$' en el token con el valor de una variable
 * de entorno.
 * Toma el token en `tokens[i]`, busca el primer '$' en su valor y lo reemplaza
 * por el contenido de `env`, actualizando el valor del token.
 * @param new_value Cadena para almacenar el nuevo valor (se sobrescribe).
 * @param tokens Arreglo de tokens.
 * @param i Índice del token a modificar.
 * @param env Valor de la variable de entorno para reemplazar.
 */
void	get_value_expanded(char *new_value, t_token **tokens, int i, char *env)
{
	char	*dollar;

	dollar = ft_strchr(tokens[i]->value, '$');
	new_value = ft_strjoin(ft_substr(tokens[i]->value, 0, dollar
				- tokens[i]->value), env);
	free(tokens[i]->value);
	tokens[i]->value = new_value;
}
