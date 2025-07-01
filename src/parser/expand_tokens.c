/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:23:52 by clalopez          #+#    #+#             */
/*   Updated: 2025/07/01 12:32:59 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../minishell.h"

/*
	PARTE DE JAVIER

*/

/**
 * @brief Funcion join pero libera memoria de los strings
 * @param s1 Primer string 
 * @param s2 Segundo string que se junta al segundo
 * @return s1 y s2 concatenados
 */
char	*strjoin_and_free(char *s1, char *s2)
{
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (tmp);
}

/**
 * @brief Concatena al resultado final una variable de entorno o texto normal.
 * Si encuentra un '$', extrae el nombre de la variable, busca su valor en
 * la lista de entorno y lo añade al resultado. Si no hay '$', concatena texto 
 * normal.
 * @param e Estructura que contiene el estado de expansión
 * @param env_list Lista de las variables de entorno
 * @param value String a procesar
 */
void	concat_result(t_expand *e, t_env *env_list, char *value)
{
	if (value[e->i] == '$')
	{
		e->start = ++e->i;
		while (value[e->i] && (ft_isalnum(value[e->i]) || value[e->i] == '_'))
			e->i++;
		e->var = ft_substr(value, e->start, e->i - e->start);
		e->env = get_env_value(env_list, e->var);
		free(e->var);
		if (e->env)
		{
			e->tmp = ft_strjoin(e->result, e->env);
			free(e->result);
			e->result = e->tmp;
		}
	}
	else
	{
		e->start = e->i;
		while (value[e->i] && value[e->i] != '$')
			e->i++;
		e->tmp = ft_substr(value, e->start, e->i - e->start);
		e->result = strjoin_and_free(e->result, e->tmp);
	}
}

/**
 * @brief Expande todas las variables de entorno.
 * Recorre la cadena value, busca variables que empiecen por el '$' y las
 * reemplaza por su valor correspondiente del env. Devuelve la
 * cadena con todas las variables expandidas.
 * @param env_list Lista de variables de entorno.
 * @param value Cadena con posibles variables a expandir.
 * @return Nueva cadena con las variables expandidas.
 */
char	*expand_all_vars(t_env *env_list, char *value)
{
	t_expand	*e;
	char		*final;

	e = malloc(sizeof(t_expand));
	e->i = 0;
	e->result = ft_strdup("");
	while (value[e->i])
		concat_result(e, env_list, value);
	final = e->result;
	free(e);
	return (final);
}

/**
 * @brief Recorre todos los tokens y si es de tipo word o dobles comillas
 * expande las variables y le cambia el valor al value del token
 * @param env_list Lista de variables de entorno.
 * @param tokens Lista de todos los tokens.
 */
void	expand_env_values(t_env *env_list, t_token **tokens)
{
	int		i;
	char	*expanded;

	i = 0;
	while (tokens[i] != NULL)
	{
		if (tokens[i]->type == TOKEN_WORD || tokens[i]->type == TOKEN_DOB_QUOTE)
		{
			expanded = expand_all_vars(env_list, tokens[i]->value);
			free(tokens[i]->value);
			tokens[i]->value = expanded;
		}
		i++;
	}
}
