/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_to_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbogad <jbogad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 12:29:17 by jaboga-d          #+#    #+#             */
/*   Updated: 2025/09/02 14:20:26 by jbogad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * @brief Busca una variable de entorno por su nombre.
 * @param env_list Lista de variables de entorno.
 * @param name Nombre de la variable a buscar.
 * @return Puntero a la variable encontrada o NULL.
 */
t_env	*find_env(t_env *env_list, char *name)
{
	t_env	*tmp;

	if (!env_list || !name)
		return (NULL);
	tmp = env_list;
	while (tmp)
	{
		if (tmp->name_env && ft_strcmp(tmp->name_env, name) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

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
