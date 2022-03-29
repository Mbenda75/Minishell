/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 22:01:53 by benmoham          #+#    #+#             */
/*   Updated: 2022/03/29 18:28:34 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_option(char *str)
{
	int	i;

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

int	ft_echo_dollar(char	**cmd, int i)
{
	int		dollar;

	dollar = 0;
	dollar = ft_count_dollars(cmd, i);
	if (dollar == 1)
	{
		ft_echo_single_dollar(cmd, i);
		return (SUCCESS);
	}
	if (dollar > 1)
	{
		ft_echo_several_dollars(cmd, i);
		return (SUCCESS);
	}
	return (SUCCESS);
}

void	ft_write_echo(char **cmd, int i, int j)
{
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			if (ft_find_dollars(cmd[i]) == SUCCESS)
			{
				j++;
				ft_echo_dollar(cmd, i);
				break ;
			}
			else
			{
				ft_putstr_fd(cmd[i], 1);
				if (cmd[i + 1])
					write(1, " ", 1);
				break ;
			}
		j++;
		}
	i++;
	}
}

int	ft_built_echo(char *cmd[])
{
	t_decompte	m;

	m.i = 1;
	m.l = 0;
	m.j = 0;
	if (ft_len(cmd) != 1)
	{
		while (cmd[m.i] && check_option(cmd[m.i]))
		{
			m.l = 1;
			m.i++;
		}
		ft_write_echo(cmd, m.i, m.j);
	}
	if (!m.l)
		write(1, "\n", 1);
	exit(127);
	return (0);
}
