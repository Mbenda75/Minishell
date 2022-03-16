/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 22:05:30 by user42            #+#    #+#             */
/*   Updated: 2022/03/16 16:26:20 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		check_option(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (i == 0 && (str[i] != '-'))
			return (0);
		if (i > 0 && (str[i] != 'n'))
			return (0);
		i++;
	}
	if (i <= 1)
		return (0);
	return (1);
}

int		ft_len(char *cmd[])
{
	int i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

int		ft_built_echo(char *cmd[])
{
	int i;
	int cmd_n;

	i = 1;
	cmd_n = 0;
	if (ft_len(cmd) != 1)
	{
		while (cmd[i] && check_option(cmd[i]))
		{
			cmd_n = 1;
			i++;
		}
		while (cmd[i])
		{
			ft_putstr_fd(cmd[i], 1);
			if (cmd[i + 1])
				write(1, " ", 1);
			i++;
		}
	}
	if (!cmd_n)
		write(1, "\n", 1);
	return (0);
}