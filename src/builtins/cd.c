/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbogad <jbogad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:06:21 by jaboga-d          #+#    #+#             */
/*   Updated: 2025/09/16 12:34:49 by jbogad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

static void	update_pwd_vars(t_shell *msh)
{
	char	*current_pwd;
	char	*new_pwd;

	current_pwd = get_var_val("PWD", msh);
	if (current_pwd)
		add_env(&(msh->env), "OLDPWD", current_pwd);
	new_pwd = getcwd(NULL, 0);
	if (new_pwd)
	{
		add_env(&(msh->env), "PWD", new_pwd);
		free(new_pwd);
	}
	if (current_pwd)
		free(current_pwd);
}

static int	go_oldpwd(t_shell *msh)
{
	char	*oldpwd;

	oldpwd = get_var_val("OLDPWD", msh);
	if (!oldpwd || ft_strlen(oldpwd) == 0)
	{
		ft_putstr_fd("cd: OLDPWD not set\n", 2);
		if (oldpwd)
			free(oldpwd);
		return (1);
	}
	if (chdir(oldpwd) != 0)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(oldpwd, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		free(oldpwd);
		return (1);
	}
	ft_putstr_fd(oldpwd, 1);
	ft_putstr_fd("\n", 1);
	free(oldpwd);
	return (0);
}

static int	go_home_or_there(t_shell *msh)
{
	char	*home;

	if (msh->cmd_args[1] == NULL)
	{
		home = get_var_val("HOME", msh);
		if (!home)
			home = ft_strdup(getenv("HOME"));
		if (!home)
			return (ft_putstr_fd("cd: HOME not set\n", 2), 1);
		if (chdir(home) != 0)
		{
			ft_putstr_fd("cd: Permission denied\n", 2);
			free(home);
			return (1);
		}
		free(home);
		return (0);
	}
	if (access(msh->cmd_args[1], F_OK) != 0)
		return (ft_putstr_fd("cd: No such file or directory\n", 2), 2);
	if (chdir(msh->cmd_args[1]) != 0)
		return (ft_putstr_fd("cd: Permission denied\n", 2), 1);
	return (0);
}

void	ft_cd(t_shell *msh)
{
	int	result;

	if (!msh || !msh->cmd_args)
	{
		if (msh)
			msh->exit_status = 1;
		return ;
	}
	if (msh->cmd_args[2] != NULL)
	{
		write(2, "cd: too many arguments\n", 23);
		msh->exit_status = 1;
		return ;
	}
	if (msh->cmd_args[1] && ft_strcmp(msh->cmd_args[1], "-") == 0)
		result = go_oldpwd(msh);
	else
		result = go_home_or_there(msh);
	if (result == 0)
		update_pwd_vars(msh);
	msh->exit_status = result;
}
