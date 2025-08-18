/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaboga-d <jaboga-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:06:30 by jaboga-d          #+#    #+#             */
/*   Updated: 2025/08/13 21:47:34 by jaboga-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
	para probar el comando exit, 
	exit 0-255 debe salir el numero 
	exit < 0 | > 255 debe salir el numero % 256

	cuando haces exit x -> haces un echo a la 
	variable $? que contiene el codigo de salida.
*/

static void	exit_error(char *str)
{
	write(2, "exit: ", 6);
	ft_putstr_fd(str, 2);
	write(2, ": numeric argument required\n", 28);
}

static void	check_valid_input(t_shell *msh, int i)
{
	if (msh->cmd_args[1][i] != '\0')
	{
		exit_error(msh->cmd_args[1]);
		msh->exit_status = 2;
		return ;
	}
	if (msh->cmd_args[2])
	{
		write(2, "exit: too many arguments\n", 26);
		msh->exit_status = 1;
		return ;
	}
	msh->exit_status = ft_atoi(msh->cmd_args[1]) % 256;
}

void	ft_exit(t_shell *msh)
{
	int	i;

	if (!msh)
		return ;
	write(2, "exit\n", 5);
	i = 0;
	if (msh->cmd_args[1])
	{
		while (msh->cmd_args[1][i] && (ft_isdigit(msh->cmd_args[1][i])
			|| (i == 0 && msh->cmd_args[1][i] == '-')))
			i++;
		check_valid_input(msh, i);
		if (msh->exit_status == 1 || msh->exit_status == 2)
			return ;
	}
	free_cmd_args(msh);
	ft_free_list(&msh->env);
	exit(msh->exit_status);
}
