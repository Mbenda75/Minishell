/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 08:07:53 by adaloui           #+#    #+#             */
/*   Updated: 2022/03/29 14:56:28 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

struct s_env	*g_list;

int	check_pipe(char *str)
{
	int	i;
	int	len;

	len = ft_strlen(str);
	i = 0;
	while (str[i])
	{
		if ((str[i] == '|' && str[i + 1] == '|' )
			|| str[0] == '|' || str[len - 1] == '|')
		{
			printf("error pipe\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	count_pipe(char *str)
{
	int	i;
	int	pipe;

	i = 0;
	pipe = 0;
	while (str[i])
	{
		if (str[i] == '|' && str[i + 1] != '|')
			pipe++;
		i++;
	}
	return (pipe);
}

int	main(int ac, char **av, char **env)
{
	if (ac != 1 && !av)
		exit(1);
	ft_signals();
	minishell(env);
	return (0);
}
