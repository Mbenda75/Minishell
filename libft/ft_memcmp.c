/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 18:56:12 by adaloui           #+#    #+#             */
/*   Updated: 2021/05/27 15:47:52 by adaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	int		result;

	i = 0;
	while (i < n)
	{
		result = ((unsigned char *)s1)[i] - ((unsigned char *)s2)[i];
		if (result != 0)
			return (result);
		i++;
	}
	return (0);
}
