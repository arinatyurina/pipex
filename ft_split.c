/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyurina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:40:27 by atyurina          #+#    #+#             */
/*   Updated: 2024/02/04 15:01:29 by atyurina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && (i < (n - 1)))
	{
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

static int	ft_count_w(char const *s, char c)
{
	int	words;
	int	i;

	i = 0;
	words = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i] != '\0')
		{
			words++;
			i++;
		}
		while (s[i] != c && s[i])
			i++;
	}
	return (words);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub;
	size_t	slen;

	i = 0;
	slen = ft_strlen(s);
	if (!s)
		return (0);
	if (slen < start)
		len = 0;
	if (len > slen)
		len = slen;
	else if (len > (slen - start))
		len = slen - start;
	sub = (char *)malloc((len + 1) * sizeof(char));
	if (!sub)
		return (0);
	while (i < len && i < slen)
	{
		sub[i] = s[start];
		i++;
		start++;
	}
	sub[i] = '\0';
	return (sub);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		start;
	char	**res;

	i = 0;
	start = 0;
	res = (char **)malloc((ft_count_w(s, c) + 1) * sizeof(char *));
	if (!res)
		return (0);
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		if (i > start)
		{
			*res++ = ft_substr(s, start, i - start);
			if (!res)
				return (0);
		}
	}
	*res = NULL;
	return (res - ft_count_w(s, c));
}
/*
#include <stdio.h>

int	main(void)
{
	const char	*s;
	char		c;
	int			i;
	char		**p;

	s = "___Hello__world_maaan_!___";
	c = '_';
	i = 0;
	p = ft_split(s, c);
	while (p[i] != NULL)
	{
		printf("%s\n", p[i]);
		i++;
	}
	if  (p[0] == NULL)
		printf("NULL");
}

Parameters s: The string to be split.
c: The delimiter character.
Return value: The array of new strings resulting from the split.
NULL if the allocation fails.
Allocates (with malloc(3)) and returns an array
of strings obtained by splitting ’s’ using the
character ’c’ as a delimiter. The array must end
with a NULL pointer.
*/
