/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 12:55:59 by adaloui           #+#    #+#             */
/*   Updated: 2021/05/27 16:52:39 by adaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_decoupe(long n_t, int signe)
{
	unsigned int	lent;

	lent = 0;
	if (n_t == 0)
		return (1);
	while (n_t > 0)
	{
		n_t = n_t / 10;
		lent++;
	}
	if (signe == -1)
		lent++;
	return (lent);
}

static void	ft_calcul(long n_t, int signe, char *str, unsigned int len)
{
	str[len] = '\0';
	str[--len] = n_t % 10 + '0';
	n_t = n_t / 10;
	while (n_t > 0)
	{
		str[--len] = n_t % 10 + '0';
		n_t = n_t / 10;
	}
	if (signe == -1)
		str[0] = '-';
}

char	*ft_itoa(int n)
{
	long			n_t;
	int				signe;
	char			*str;
	unsigned int	len;

	signe = 1;
	if (n < 0)
	{
		n_t = (long)n * -1;
		signe = -1;
	}
	else
		n_t = n;
	len = ft_decoupe(n_t, signe);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	ft_calcul(n_t, signe, str, len);
	return (str);
}
