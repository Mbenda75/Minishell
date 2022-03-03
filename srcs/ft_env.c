/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 21:10:54 by user42            #+#    #+#             */
/*   Updated: 2022/03/03 19:59:12 by adaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_built_in_env(char **built_in, char **env)
{
	int i;
	int j;

	i = 0;
	for ( int i = 0; env[i];i++)
	printf("s == %s\n", env[i]);
	if (built_in[1])
		ft_custom_error("env: aucun argument n'est possible");
	else
	{
		while (g_list->envp_2[i])
		{
			j = 0;
			while (g_list->envp_2[i][j] && g_list->envp_2[i][j] != '\n')
			{
				ft_putchar_fd(g_list->envp_2[i][j], 0);
				j++;
			}
			ft_putchar_fd('\n', 0);
		//	printf("i = %d\n", i);
			i++;
		}
	}
}