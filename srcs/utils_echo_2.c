/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_echo_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:24:55 by adaloui           #+#    #+#             */
/*   Updated: 2022/03/23 13:30:34 by adaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_len(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

int	ft_count_dollars(char **cmd, int i)
{
	int	dollar;
	int	j;

	dollar = 0;
	j = 0;
	while (cmd[i][j])
	{
		if (cmd[i][j] == '$')
			dollar++;
		j++;
	}
	return (dollar);
}
