/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrschr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 12:35:45 by adaloui           #+#    #+#             */
/*   Updated: 2021/05/27 15:35:21 by adaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (s[i] == '\0' && c == '\0')
		return ((char *)&s[i]);
	while (s[i] != '\0')
		i++;
	while (s[i] >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		if (i == 0)
			return (NULL);
		i--;
	}
	return (NULL);
}
