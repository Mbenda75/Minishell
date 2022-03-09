/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 21:10:54 by user42            #+#    #+#             */
/*   Updated: 2022/03/09 16:27:42 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env *file_env(char *str, int i)
{
	t_env *lst;
	
	lst = malloc(sizeof(t_env));
	lst->content = str;
	lst->index_env = i;
	lst->next = NULL;
	return (lst);	
}

int limit_env(char **env)
{
	int i;

	i = 1;
	while (env[i])
		i++;
	return (i);
}

t_env	*cpy_env(char **env)
{
	t_env *tmp;
	int i;
	
	tmp = g_list;
	i = 1;
	while (env[i])
	{
		if (!g_list)
		{
			g_list = file_env(env[i], i);
			tmp = g_list;
		}
		else
		{
			tmp->next = file_env(env[i], i);
			tmp = tmp->next;
		}
		i++;
	}
	g_list->limit_free = limit_env(env);
	return (g_list);	
}

void	ft_built_in_env(char **built_in)
{
	int i;
	t_env *head;
	t_env *tail;

	i = 0;
	head = g_list;
	tail = head;
	if (built_in[1])
		ft_custom_error("env: aucun argument n'est possible");
	else
	{
		while (tail != NULL)
		{
			printf("adrresenv== %p\n", tail->content);
			printf("env == %s\n", tail->content);
			tail = tail->next;
		}
	}
}