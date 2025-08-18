/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaboga-d <jaboga-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:06:21 by jaboga-d          #+#    #+#             */
/*   Updated: 2025/08/18 10:55:23 by jaboga-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * @brief Obtiene el valor de una variable de entorno desde msh->env.
 * @param var_name Nombre de la variable (ej: "HOME").
 * @param msh Estructura principal del shell.
 * @return Valor de la variable o NULL si no existe.
 */
static char	*get_var_val(char *var_name, t_shell *msh)
{
	t_env	*tmp;
	char	*result;

	if (!var_name || !msh || !msh->env)
		return (NULL);
	tmp = msh->env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name_env, var_name) == 0)
		{
			if (tmp->val_env)
				result = ft_strdup(tmp->val_env);
			else
				result = ft_strdup("");
			return (result);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

/**
 * @brief Cambia al directorio especificado.
 * @param msh Estructura principal del shell.
 * @return 0 si éxito, código de error si falla.
 */
static int	go_there(t_shell *msh)
{
	char	*path;

	path = msh->cmd_args[1];
	if (access(path, F_OK) != 0)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (2);
	}
	if (chdir(path) != 0)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		return (1);
	}
	return (0);
}

/**
 * @brief Cambia al directorio HOME.
 * @param msh Estructura principal del shell.
 * @return 0 si éxito, código de error si falla.
 */
static int	go_home(t_shell *msh)
{
	char	*home;

	home = get_var_val("HOME", msh);
	if (!home)
	{
		home = getenv("HOME");
		if (!home)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return (1);
		}
		home = ft_strdup(home);
	}
	if (chdir(home) != 0)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(home, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		free(home);
		return (1);
	}
	free(home);
	return (0);
}

/**
 * @brief Ejecuta el comando cd.
 * @param msh Estructura principal del shell.
 */
void	ft_cd(t_shell *msh)
{
	printf("[DEBUG] ft_cd INICIO\n");
	
	if (!msh || !msh->cmd_args)
	{
		printf("[DEBUG] msh o cmd_args es NULL - RETORNANDO\n");
		if (msh)
			msh->exit_status = 1;
		return ;
	}
	
	printf("[DEBUG] cmd_args[0]: '%s'\n", msh->cmd_args[0]);
	printf("[DEBUG] cmd_args[1]: %s\n", msh->cmd_args[1] ? msh->cmd_args[1] : "NULL");
	
	if (msh->cmd_args[1] == NULL)
	{
		printf("[DEBUG] Sin argumentos, llamando go_home\n");
		msh->exit_status = go_home(msh);
		printf("[DEBUG] go_home retornó: %d\n", msh->exit_status);
		printf("[DEBUG] ft_cd TERMINANDO - SIN ARGS\n");
		return ;
	}
	if (msh->cmd_args[2] != NULL)
	{
		printf("[DEBUG] Demasiados argumentos\n");
		write(2, "cd: too many arguments\n", 23);
		msh->exit_status = 1;
		printf("[DEBUG] ft_cd TERMINANDO - MUCHOS ARGS\n");
		return ;
	}
	printf("[DEBUG] Con argumentos, llamando go_there\n");
	msh->exit_status = go_there(msh);
	printf("[DEBUG] go_there retornó: %d\n", msh->exit_status);
	printf("[DEBUG] ft_cd TERMINANDO - CON ARGS\n");
}