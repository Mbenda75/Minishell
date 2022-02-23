/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 18:55:13 by adaloui           #+#    #+#             */
/*   Updated: 2021/05/27 15:40:24 by adaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char				*dst2;
	const char			*src2;
	char				*dst3;
	const char			*src3;

	dst2 = dst;
	src2 = src;
	if (dst2 == NULL && src2 == NULL)
		return (NULL);
	if (dst2 < src2)
	{
		while (len--)
			*dst2++ = *src2++;
	}
	else
	{
		src3 = src2 + (len - 1);
		dst3 = dst2 + (len - 1);
		while (len--)
			*dst3-- = *src3--;
	}
	return (dst);
}
