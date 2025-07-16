/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaboga-d <jaboga-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:06:33 by jaboga-d          #+#    #+#             */
/*   Updated: 2025/07/15 22:30:03 by jaboga-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void		ft_export_without_arg(t_shell *msh);
static t_env	*copy_list(t_env *lst);
static int		check_export(char *arg);
static int		is_valid_name(char *name);

/**
 * @brief Ejecuta el comando export con o sin argumentos.
 * @param msh Estructura principal con variables de entorno.
 */
void	ft_export(t_shell *msh)
{
	int	i;

	if (!msh)
		return ;
	msh->exit_status = 0;
	if (!msh->cmd_args || msh->count_cmd_args <= 1)
	{
		ft_export_without_arg(msh);
		return ; 
	}
	i = 1;
	while (i < msh->count_cmd_args && msh->cmd_args[i])
	{
		if (check_export(msh->cmd_args[i]))
			add_arg_to_env(msh->cmd_args[i], msh);
		else
			msh->exit_status = 1;
		i++;
	}
}

/**
 * @brief Muestra todas las variables de entorno en formato declare.
 * @param msh Estructura principal con variables de entorno.
 */
static void	ft_export_without_arg(t_shell *msh)
{
	t_env	*tmp;
	t_env	*lst_cpy;

	if (!msh || !msh->env)
		return ;
	lst_cpy = copy_list(msh->env);
	tmp = lst_cpy;
	while (tmp)
	{
		if (tmp->val_env && tmp->val_env[0])
			printf("declare -x %s=\"%s\"\n", tmp->name_env, tmp->val_env);
		else
			printf("declare -x %s\n", tmp->name_env);
		tmp = tmp->next;
	}
	ft_free_list(&lst_cpy);
}

/**
 * @brief Crea una copia de la lista de variables de entorno.
 * @param lst Lista original de variables de entorno.
 * @return Nueva lista copiada o NULL si error.
 */
static t_env	*copy_list(t_env *lst)
{
	t_env	*cpy;
	t_env	*tmp;

	if (!lst)
		return (NULL);
	cpy = NULL;
	tmp = lst;
	while (tmp)
	{
		if (tmp->name_env)
		{
			if (!cpy)
				cpy = ft_lstnew_env(tmp->name_env, tmp->val_env, 1);
			else
				ft_lstadd_back_env(&cpy, ft_lstnew_env(tmp->name_env,
						tmp->val_env, 1));
		}
		tmp = tmp->next;
	}
	return (cpy);
}

/**
 * @brief Valida si un argumento de export es correcto.
 * @param arg Argumento a validar (formato: VAR=value o VAR).
 * @return 1 si es válido, 0 si no.
 */
static int	check_export(char *arg)
{
    char	*name;
    char	*equal_pos;
    int		result;

    if (!arg || arg[0] == '=' || ft_isdigit(arg[0]))
    {
        printf("export: %s: not a valid identifier\n", arg);
        return (0);
    }
    equal_pos = ft_strchr(arg, '=');
    if (equal_pos)
        name = ft_substr(arg, 0, equal_pos - arg);
    else
        name = ft_strdup(arg);
    if (!name)
        return (0);
    result = is_valid_name(name);
    if (!result)
        printf("export: %s: not a valid identifier\n", arg);
    free(name);
    return (result);
}

/**
 * @brief Verifica si un nombre de variable es válido.
 * @param name Nombre de variable a verificar.
 * @return 1 si es válido, 0 si no.
 */
static int	is_valid_name(char *name)
{
    int	i;

    if (!name || !name[0] || ft_isdigit(name[0]))
        return (0);
    i = 0;
    while (name[i])
    {
        if (!ft_isalnum(name[i]) && name[i] != '_')
            return (0);
        i++;
    }
    return (1);
}
