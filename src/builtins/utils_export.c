/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaboga-d <jaboga-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 12:19:22 by jaboga-d          #+#    #+#             */
/*   Updated: 2025/07/16 11:56:14 by jaboga-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	update_existing_var(t_env *var, char *value);
static void	add_new_var(t_shell *msh, char *name, char *value);

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

/**
 * @brief Añade una nueva variable de entorno a la lista.
 * @param env_list Puntero a la lista de variables.
 * @param name Nombre de la variable.
 * @param value Valor de la variable.
 */
void	add_env(t_env **env_list, char *name, char *value)
{
	t_env	*new;

	if (!env_list || !name)
		return ;
	new = ft_lstnew_env(name, value, 1);
	if (!new)
		return ;
	if (!*env_list)
		*env_list = new;
	else
		ft_lstadd_back_env(env_list, new);
}

/**
 * @brief Procesa un argumento de export y lo añade al entorno.
 * @param arg Argumento en formato "VAR=value" o "VAR".
 * @param msh Estructura principal del shell.
 */
void	add_arg_to_env(char *arg, t_shell *msh)
{
	char	*equal;
	char	*name;
	char	*value;
	t_env	*var;

	equal = ft_strchr(arg, '=');
	if (equal)
	{
		name = ft_substr(arg, 0, equal - arg);
		value = ft_strdup(equal + 1);
		var = find_env(msh->env, name);
		if (var)
			update_existing_var(var, value);
		else
			add_new_var(msh, name, value);
		free(name);
		free(value);
	}
	else
		if (!find_env(msh->env, arg))
				add_env(&(msh->env), arg, "");
}

/**
 * @brief Actualiza el valor de una variable existente.
 * @param var Variable de entorno a actualizar.
 * @param value Nuevo valor para la variable.
 */
static void	update_existing_var(t_env *var, char *value)
{
	free(var->val_env);
	var->val_env = ft_strdup(value);
}

/**
 * @brief Añade una nueva variable al entorno.
 * @param msh Estructura principal del shell.
 * @param name Nombre de la nueva variable.
 * @param value Valor de la nueva variable.
 */
static void	add_new_var(t_shell *msh, char *name, char *value)
{
	add_env(&(msh->env), name, value);
}
