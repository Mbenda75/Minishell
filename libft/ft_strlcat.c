/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 12:47:13 by adaloui           #+#    #+#             */
/*   Updated: 2021/05/22 12:58:29 by adaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	taille_src;
	unsigned int	taille_dest;
	unsigned int	len;

	len = 0;
	taille_dest = 0;
	taille_src = 0;
	while (dst[taille_dest])
		taille_dest++;
	while (src[taille_src])
		taille_src++;
	if (size <= taille_dest)
		taille_src += size;
	else
		taille_src += taille_dest;
	while (src[len] && taille_dest + 1 < size)
	{
		dst[taille_dest] = src[len];
		len++;
		taille_dest++;
	}
	dst[taille_dest] = '\0';
	return (taille_src);
}
