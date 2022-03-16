/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 22:05:30 by user42            #+#    #+#             */
/*   Updated: 2022/03/16 16:16:59 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		valid_option(char *now)
{
	int i;

	i = 0;
	while (now[i])
	{
		if (i == 0 && (now[i] != '-'))
			return (0);
		if (i > 0 && (now[i] != 'n'))
			return (0);
		i++;
	}
	if (i <= 1)
		return (0);
	return (1);
}

int		ft_len(char *args[])
{
	int i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int		ft_echo(char *args[])
{
	int i;
	int is_n;

	i = 1;
	is_n = 0;
	if (ft_len(args) != 1)
	{
		while (args[i] && valid_option(args[i]))
		{
			is_n = 1;
			i++;
		}
		while (args[i])
		{
			ft_putstr_fd(args[i], 1);
			if (args[i + 1])
				write(1, " ", 1);
			i++;
		}
	}
	if (!is_n)
		write(1, "\n", 1);
	return (0);
}