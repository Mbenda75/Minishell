/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 17:40:02 by user42            #+#    #+#             */
/*   Updated: 2022/03/18 16:26:32 by adaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*ft_list_push_back(t_env *cpy_env, char *str)
{
	t_env	*list;
	int		i;

	list = cpy_env;
	i = 1;
	if (list)
	{
		while (list->next)
		{
			list = list->next;
			i++;
		}
		i++;
		list->next = file_env(str, i);
	}
	return (list);
}

t_env	*ft_modify_lst(t_env *lst, char *env_var_cpy, char *env_var)
{
	t_env	*head;
	t_env	*tail;
	char	*str;

	head = lst;
	tail = head;
	str = ft_strjoin(env_var_cpy, "=");
	while (head != NULL)
	{
		if (ft_strncmp(head->content, str, ft_strlen(env_var_cpy)) == 0)
		{
			free(head->content);
			head->content = env_var;
			break ;
		}
		head = head->next;
	}
	if (head == NULL)
		head = ft_list_push_back(lst, env_var);
	free(str);
	return (lst);
}

int	ft_built_in_export_modify(char *env_var, char *apres_egal)
{
	char	*env_var_cpy;
	char	*tmp;
	char	*env_var2;

	if (ft_strchr(env_var, '='))
	{
		env_var_cpy = ft_strdup(env_var);
		env_var = ft_strjoin(env_var, "");
		g_list = ft_modify_lst(g_list, env_var_cpy, env_var);
		free(env_var_cpy);
	}
	else
	{
		env_var = ft_strjoin(env_var, "=");
		env_var_cpy = ft_strdup(env_var);
		env_var2 = ft_strjoin(env_var, apres_egal); // need to correct leak
		free(env_var);
		g_list = ft_modify_lst(g_list, env_var_cpy, env_var2);
		free(env_var_cpy);
	}
	return (SUCCESS);
}

int	ft_built_in_export_add(char *env_var, char *apres_egal)
{
	t_env	*head;
	t_env	*tail;
	char	*tmp;
	char	*before_equal;

	if (ft_check_variable_before_equal(env_var) == 1)
		return (FAILURE);
	if (ft_check_variable_after_equal(apres_egal) == 1)
		return (FAILURE);
	printf("APRES_egal = %s\n", apres_egal);
/* 	if (ft_strrchr(env_var, '+'))
	{
		before_equal = ft_trim_name(env_var);
		apres_egal = ft_add_content(before_equal, apres_egal);
	} */
	if (ft_strchr(apres_egal, '$'))
	{
		apres_egal = ft_add_env_var(apres_egal, env_var);
		printf("APRES_egal = %s\n", apres_egal);

	}
	printf("APRES_egal = %s\n", apres_egal);
	head = g_list;
	tail = head;
	while (head != NULL)
	{
		if (ft_strncmp(head->content, before_equal, ft_strlen(before_equal)) == 0)
		{
			ft_built_in_export_modify(before_equal, apres_egal);
			return (SUCCESS);
		}
		head = head->next;
	}
	if (ft_strchr(before_equal, '='))
	{
		tmp = before_equal;
		before_equal = ft_strjoin(before_equal, apres_egal);
		free(tmp);
	}
	else
	{
		before_equal = ft_strjoin(before_equal, "=");
		tmp = before_equal;
		before_equal = ft_strjoin(before_equal, apres_egal); // need to correct leaks
		free(tmp);
	}
	tail = ft_list_push_back(g_list, before_equal);

	return (SUCCESS);
}

int	ft_built_in_export(char **cmd)
{
	char		*env_var;
	char		temp;
	t_decompte	k;

	env_var = NULL;
	k.l = 0;
	if (cmd[1] == NULL)
		ft_built_in_env(cmd);
	else
	{
		while (cmd[++k.l])
		{	
			env_var = cmd[k.l];
			k.i = ft_find_the_equal(env_var);
			if (k.i == 0)
			{
				k.j = ft_find_where_is_equal(env_var);
				temp = env_var[k.j];
				env_var[k.j] = 0;
				ft_built_in_export_add(env_var, env_var + k.j + 1);
				env_var[k.j] = temp;
			}
			if (k.i == 2)
			{
				k.j = ft_find_where_is_equal(env_var);
				ft_built_in_export_add(env_var, env_var + k.j + 1);
			}
		}
	}
	return (SUCCESS);
}
