/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 21:10:54 by user42            #+#    #+#             */
/*   Updated: 2022/03/22 15:15:43 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*file_env(char *str)
{
	t_env	*lst;

	lst = malloc(sizeof(t_env));
	lst->content = str;
	lst->next = NULL;
	return (lst);
}

int	limit_env(char **env)
{
	int	i;

	i = 1;
	while (env[i])
		i++;
	return (i);
}

t_env	*cpy_env(char **env)
{
	t_env	*tmp;
	int		i;

	tmp = g_list;
	i = 1;
	while (env[i])
	{
		if (!g_list)
		{
			g_list = file_env(ft_strdup(env[i]));
			tmp = g_list;
		}
		else
		{
			tmp->next = file_env(ft_strdup(env[i]));
			tmp = tmp->next;
		}
		i++;
	}
	return (g_list);
}

int	ft_built_in_env(char **built_in)
{
	t_env	*head;
	t_env	*tail;
	int		i;

	i = 0;
	head = g_list;
	tail = head;
	/*while (built_in[i])
	{
		if (ft_strcmp(built_in[i], "env") != 0 || ft_strcmp(built_in[i], ">") != 0)
		{
			printf("env: '%s' OUINo such file or directory\n", built_in[i]);
			return (FAILURE);
		}
		i++;
	}*/
	while (tail != NULL)
	{
		if (tail->content)
			printf("env == %s\n", tail->content);
		tail = tail->next;
	}
	return (SUCCESS);
}
