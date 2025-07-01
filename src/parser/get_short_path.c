/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_short_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 12:34:02 by clalopez          #+#    #+#             */
/*   Updated: 2025/07/01 12:17:37 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * @brief Contar cuantos caracteres hay despues de la segunda
	/ para hacer malloc
 * @param route Toda la ruta absoluta Ej: clalopez/home/documents/minishell
 * @return Devuelve la cantidad en caracteres a partir del segundo /
 */
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

/**
 * @brief Funcion para coger un string con lo que hay a partir del segundo /
 * @param route Toda la ruta absoluta Ej: clalopez/home/documents/minishell
 * @param len Tamaño del string
 * @return Devuelve un string a partir del segundo /
 */
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

/**
 * @brief Funcion para obtener la ruta como en bash
 * @return Devuelve un string con la ruta actual mas el $
 */
char	*get_short_path(void)
{
	char	*cwd;
	char	*route;
	char	*result;
	int		len;

	cwd = getcwd(NULL, 0);
	route = ft_strjoin(cwd, "$ ");
	free(cwd);
	len = count_chars_after_second_slash(route);
	result = extract_short_path(route, len);
	free(route);
	return (result);
}
