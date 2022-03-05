/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 21:10:54 by user42            #+#    #+#             */
/*   Updated: 2022/03/05 15:30:11 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env *file_env(char *str)
{
	t_env *lst;
	
	lst = malloc(sizeof(t_env));
	lst->content = str;
	lst->next = NULL;
	return (lst);	
}

t_env	*cpy_env(char **envp)
{
	t_env *cpy_env;
	t_env *tmp;
	int i;

	tmp = NULL;
	cpy_env = NULL;
	i = 0;
	while (envp[i])
	{
		if (!cpy_env)
		{
			cpy_env = file_env(envp[i]);
			tmp = cpy_env;
		}
		else
		{
			tmp->next = file_env(envp[i]);
			tmp = tmp->next;
		}
		i++;
	}
	return (cpy_env);	
}

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