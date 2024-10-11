/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stescaro <stescaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:55:22 by stescaro          #+#    #+#             */
/*   Updated: 2024/01/29 11:10:24 by stescaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_freesplit(char **s)
{
	int	a;

	a = 0;
	while (s[a])
	{
		free(s[a]);
		a++;
	}
	free(s);
	return (1);
}

static int	count(char const *cs, char c)
{
	int	i;

	i = 0;
	while (cs[i] != c && cs[i] != '\0')
	{
		i++;
	}
	return (i);
}

static size_t	ft_count(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i])
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

static char	**split2(char const *s, char c, char **str, int a)
{
	int	t;

	while (*s)
	{
		t = count(s, c);
		if (t)
		{
			str[a] = (char *)malloc((t + 1) * sizeof(char));
			if (!str[a])
			{
				ft_freesplit(str);
				return (NULL);
			}
			while (*s != c && *s != '\0')
				*str[a]++ = *s++;
			*str[a] = '\0';
			str[a] = str[a] - t;
			a++;
		}
		else
			s++;
	}
	str[a] = NULL;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	size_t	t;

	t = ft_count(s, c);
	str = (char **)malloc((t + 1) * sizeof (char *));
	if (!str)
		return (NULL);
	str = split2(s, c, str, 0);
	return (str);
}
