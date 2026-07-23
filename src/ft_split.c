/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabed <moabed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 16:26:57 by mohammad          #+#    #+#             */
/*   Updated: 2026/07/23 18:30:00 by moabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/header.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*c;
	size_t	i;

	c = (char *)malloc(ft_strlen(s) + 1);
	if (!c)
		return (NULL);
	i = 0;
	while (s[i])
	{
		c[i] = s[i];
		i++;
	}
	c[i] = '\0';
	return (c);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sus;
	size_t	i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	sus = (char *)malloc(len + 1);
	if (!sus)
		return (NULL);
	i = 0;
	while (i < len)
	{
		sus[i] = s[start + i];
		i++;
	}
	sus[i] = '\0';
	return (sus);
}

static size_t	count_word(char const *s, char c)
{
	size_t	cw;
	size_t	i;

	cw = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i])
			cw++;
		while (s[i] != c && s[i])
			i++;
	}
	return (cw);
}

static void	spfree(char **nn, int i)
{
	while (i >= 0)
		if (nn[i])
			free(nn[i--]);
	free(nn);
}

static size_t	wordlen(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

static void	split_iter(char const *s, char c, char **nn)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			nn[j] = ft_substr(s, (unsigned int)i, wordlen(&s[i], c));
			if (!nn[j])
				spfree(nn, (int)(j));
			j++;
			i += wordlen(&s[i], c);
		}
	}
}

char	**ft_split(char const *s, char c)
{
	char	**nn;

	if (!s)
		return (NULL);
	nn = malloc(sizeof(char *) * (count_word(s, c) + 1));
	if (!nn)
		return (NULL);
	nn[count_word(s, c)] = NULL;
	split_iter(s, c, nn);
	return (nn);
}
