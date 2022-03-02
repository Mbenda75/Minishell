/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 19:15:19 by adaloui           #+#    #+#             */
/*   Updated: 2022/03/02 13:27:09 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static char	*ft_strnndup(const char *s1, int c)
{
	int		i;
	char	*str;

	i = 0;
	while (s1[i] && s1[i] != c)
		i++;
	str = (char *)malloc(sizeof(char) * ++i);
	if (!str)
		return (0);
	i = 0;
	while (s1[i] && s1[i] != c)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static int	ft_counting(const char *str, char c)
{
	int	nb;
	int	i;

	i = 0;
	nb = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i] && str[i] != c)
		{
			nb++;
			while (str[i] && str[i] != c)
				i++;
		}
	}
	return (nb);
}

char	**ft_split(const char *str, char c)
{
	int		i;
	int		k;
	char	**tab;

	if (!str)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * (ft_counting(str, c) + 1));
	if (!tab)
		return (0);
	i = 0;
	k = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i] && str[i] != c)
		{
			tab[k] = ft_strnndup(str + i, c);
			k++;
		}
		while (str[i] && str[i] != c)
			i++;
	}
	tab[k] = 0;
	return (tab);
}

