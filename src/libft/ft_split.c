/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clalopez <clalopez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 10:18:30 by clalopez          #+#    #+#             */
/*   Updated: 2025/01/27 13:01:16 by clalopez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

size_t	count_words(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i] == c)
		i++;
	if (s[i] == '\0')
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			count++;
		i++;
	}
	return (count + 1);
}

char	*get_word(char const *s, char c, size_t *i)
{
	size_t	start;
	size_t	len;
	char	*word;

	while (s[*i] == c)
		(*i)++;
	start = *i;
	while (s[*i] != '\0' && s[*i] != c)
		(*i)++;
	len = *i - start;
	word = (char *)malloc(len + 1);
	if (!word)
		return (NULL);
	len = 0;
	while (len < (*i - start))
	{
		word[len] = s[start + len];
		len++;
	}
	word[len] = '\0';
	return (word);
}

void	free_array(char **array)
{
	size_t	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	**fill_result(char const *s, char c, size_t num_words)
{
	char	**result;
	size_t	i;
	size_t	j;

	result = (char **)malloc((num_words + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (j < num_words)
	{
		result[j] = get_word(s, c, &i);
		if (!result[j])
		{
			free_array(result);
			return (NULL);
		}
		j++;
	}
	result[j] = NULL;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;

	if (!s)
		return (NULL);
	if (c == '\0')
	{
		result = (char **)malloc(2 * sizeof(char *));
		if (!result)
			return (NULL);
		if (s[0] == '\0')
			result[0] = NULL;
		else
		{
			result[0] = ft_strdup(s);
			if (!result[0])
			{
				free(result);
				return (NULL);
			}
		}
		result[1] = NULL;
		return (result);
	}
	return (fill_result(s, c, count_words(s, c)));
}

//cc -Wall -Wextra -Werror -o test_split ft_split.c ft_strdup.c
/*int main(void)
{
	char *str = "Hola claudio 42";
	char del = ' ';
	char **result;
	size_t i;

	result = ft_split(str, del);

	i = 0;
	while (result[i])
	{
		printf("%s\n", result[i]);
		i++;
	}
	return (0);
}*/