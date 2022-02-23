/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 18:54:22 by adaloui           #+#    #+#             */
/*   Updated: 2021/05/27 15:41:37 by adaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*dest;
	const char	*src2;

	i = 0;
	dest = dst;
	src2 = src;
	if (dest == NULL && src2 == NULL)
		return (NULL);
	while (i < n)
	{
		dest[i] = src2[i];
		i++;
	}
	return (dest);
}
