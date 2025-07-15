/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_to_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaboga-d <jaboga-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 12:29:17 by jaboga-d          #+#    #+#             */
/*   Updated: 2025/07/15 15:47:15 by jaboga-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	assign_values(t_env *new_node, char *name, char *value, int alloc);

/**
 * @brief Crea un nuevo nodo de variable de entorno.
 * @param name Nombre de la variable.
 * @param value Valor de la variable.
 * @param alloc Si debe duplicar las strings (1) o asignar directamente (0).
 * @return Nuevo nodo creado o NULL si error.
 */
t_env	*ft_lstnew_env(char *name, char *value, int alloc)
{
	t_env	*new_node;

	new_node = ft_calloc(1, sizeof(t_env));
	if (!new_node)
		return (NULL);
	assign_values(new_node, name, value, alloc);
	new_node->next = NULL;
	return (new_node);
}

/**
 * @brief Asigna valores al nodo según el modo de asignación.
 * @param new_node Nodo donde asignar los valores.
 * @param name Nombre de la variable.
 * @param value Valor de la variable.
 * @param alloc Modo de asignación (duplicar o referencia directa).
 */
static void	assign_values(t_env *new_node, char *name, char *value, int alloc)
{
	if (alloc)
	{
		new_node->name_env = ft_strdup(name);
		if (value)
			new_node->val_env = ft_strdup(value);
		else
			new_node->val_env = ft_strdup("");
	}
	else
	{
		new_node->name_env = name;
		new_node->val_env = value;
	}
}

/**
 * @brief Añade un nodo al final de la lista de variables de entorno.
 * @param lst Puntero a la lista de variables.
 * @param new Nuevo nodo a añadir.
 */
void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

/**
 * @brief Extrae el nombre de una variable del formato "NAME=value".
 * @param fullenv String en formato "NAME=value".
 * @return Nombre de la variable extraído.
 */
char	*get_env_name(char *fullenv)
{
	int	i;

	if (!fullenv)
		return (ft_strdup(""));
	i = 0;
	while (fullenv[i] && fullenv[i] != '=')
		i++;
	return (ft_substr(fullenv, 0, i));
}

/**
 * @brief Extrae el valor de una variable del formato "NAME=value".
 * @param fullenv String en formato "NAME=value".
 * @return Valor de la variable extraído.
 */
char	*get_value_of_env(char *fullenv)
{
	char	*equal;

	if (!fullenv)
		return (ft_strdup(""));
	equal = ft_strchr(fullenv, '=');
	if (equal)
		return (ft_strdup(equal + 1));
	return (ft_strdup(""));
}
