/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 12:55:18 by adaloui           #+#    #+#             */
/*   Updated: 2021/05/27 16:33:03 by adaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_compteur(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	while (s1[i] != '\0')
		i++;
	while (s2[j] != '\0')
		j++;
	k = i + j;
	return (k);
}

char	*filler(char *str, char const *s1, char const *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		str[j] = s1[i];
		i++;
		j++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		str[j] = s2[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		k;
	char	*str;

	str = NULL;
	if (!s1 || !s2)
		return (NULL);
	k = ft_compteur(s1, s2);
	str = (char *)malloc(sizeof(char) * (k + 1));
	if (str == NULL)
		return (NULL);
	return (filler(str, s1, s2));
}
