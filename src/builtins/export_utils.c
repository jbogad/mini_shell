/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbogad <jbogad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 12:45:00 by jbogad           #+#    #+#             */
/*   Updated: 2025/09/01 12:45:00 by jbogad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
** Muestra todas las variables de entorno en formato declare
** Sin argumentos, export muestra todas las variables
*/
void	ft_export_without_arg(t_shell *msh)
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

/*
** Crea una copia de la lista de variables de entorno
** Retorna nueva lista copiada o NULL si error
*/
t_env	*copy_list(t_env *lst)
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

/*
** Verifica si un nombre de variable es válido
** Retorna 1 si es válido, 0 si no
*/
int	is_valid_name(char *name)
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

/*
** Valida si un argumento de export es correcto
** Formato: VAR=value o VAR
** Retorna 1 si es válido, 0 si no
*/
int	check_export(char *arg)
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
		printf("export: %s: not a valid identifier\n", name);
	free(name);
	return (result);
}
