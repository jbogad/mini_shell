/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_short_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 12:34:02 by clalopez          #+#    #+#             */
/*   Updated: 2025/05/28 12:42:48 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* Este archivo es para pillar la ruta absoluta y coger lo que hay
despues de la tercera / para ponerlo como ruta.
Ej: /home/clalopez/Documents/mini-shell -> /Documents/mini-shell$ */

int	count_chars_after_second_slash(char *route)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while (route[i] != '\0')
	{
		if (route[i] == '/')
			count++;
		if (count > 2)
			j++;
		i++;
	}
	return (j);
}

char	*extract_short_path(char *route, int len)
{
	char	*aux;
	int		i;
	int		k;
	int		count;

	aux = malloc(len + 1);
	if (!aux)
		return (NULL);
	i = 0;
	k = 0;
	count = 0;
	while (route[i] != '\0')
	{
		if (route[i] == '/')
			count++;
		if (count > 2)
			aux[k++] = route[i];
		i++;
	}
	aux[k] = '\0';
	return (aux);
}

char	*get_short_path(void)
{
	char *cwd;
	char *route;
	char *result;
	int len;

	cwd = getcwd(NULL, 0);
	route = ft_strjoin(cwd, "$ ");
	free(cwd);
	len = count_chars_after_second_slash(route);
	result = extract_short_path(route, len);
	free(route);
	return (result);
}