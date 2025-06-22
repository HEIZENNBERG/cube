/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onajem <onajem@student.42.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:19:28 by onajem            #+#    #+#             */
/*   Updated: 2025/06/22 20:06:26 by onajem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"

int ft_space(int ch) 
{
    char *spaces;
    int i;
	
	spaces = " \t\n\v\f\r";
	i = 0;
    while (spaces[i]) {
        if (ch == spaces[i])
            return (1);
        i++;
    }
    return 0;
}

static int	count_words(char const *s)
{
	int	i;
	int	words;

	if (!s)
		return (0);
	i = 0;
	words = 0;
	printf("-> %s\n", s);
	while (s[i])
	{
		if ((!ft_space(s[i]) && ft_space(s[i + 1])) || (!ft_space(s[i]) && s[i + 1] == '\0'))
			words++;
		i++;
	}
	return (words);
}

static void	get_lim(char const *s, size_t *start, size_t *end)
{
	while (ft_space(s[*end]))
		(*end)++;
	*start = *end;
	while (!ft_space(s[*end])&& s[*end])
		(*end)++;
}

static void	fill_array(char *dest, const char *s, size_t *start, size_t *end)
{
	size_t	i;

	i = 0;
	while (*start < *end)
		dest[i++] = s[(*start)++];
	dest[i] = '\0';
}

void	*free_array(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (NULL);
}

char	**ft_split(char const *s)
{
	size_t	words;
	size_t	start;
	size_t	end;
	size_t	i;
	char	**dest;

	if (!s)
		return (NULL);
	words = count_words(s);
	dest = (char **)malloc((words + 1) * sizeof(char *));
	if (!dest)
		return (NULL);
	dest[words] = NULL;
	i = 0;
	start = 0;
	end = 0;
	while (i < words)
	{
		get_lim(s, &start, &end);
		dest[i] = (char *)malloc(end - start + 1);
		if (!dest[i])
			return (free_array(dest));
		fill_array(dest[i++], s, &start, &end);
	}
	return (dest);
}