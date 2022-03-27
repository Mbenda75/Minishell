/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pars_quote2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 10:44:12 by benmoham          #+#    #+#             */
/*   Updated: 2022/03/27 23:18:32 by adaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_dquote(char *str, int quote)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (str[i])
	{
		if (str[i] == 34 && quote == 1)
			size++;
		if (str[i] == 39 && quote == 0)
			size++;
		i++;
	}
	size = size / 2;
	if (size % 2 == 0)
		return (0);
	return (1);
}
