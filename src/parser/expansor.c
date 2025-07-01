/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:02:34 by clalopez          #+#    #+#             */
/*   Updated: 2025/07/01 12:22:25 by clalopez         ###   ########.fr       */
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
