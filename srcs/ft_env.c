/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 21:10:54 by user42            #+#    #+#             */
/*   Updated: 2022/03/04 16:50:13 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_built_in_env(char **built_in, char **env)
{
	int i;
	int j;

	i = 0;
	if (built_in[1])
		ft_custom_error("env: aucun argument n'est possible");
	else
	{
		while (env[i])
		{
			j = 0;
			while (env[i][j] && env[i][j] != '\n')
			{
				ft_putchar_fd(env[i][j], 0);
				j++;
			}
			ft_putchar_fd('\n', 0);
		//	printf("i = %d\n", i);
			i++;
		}
	}
}