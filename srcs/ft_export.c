/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 17:40:02 by user42            #+#    #+#             */
/*   Updated: 2022/03/28 21:31:34 by adaloui          ###   ########.fr       */
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
		list->next = fill_env(str);
	}
	printf("JE SUIS LE N6\n");
	return (list);
}

t_env	*ft_modify_lst(t_env *lst, char *env_var_cpy, char *env_var)
{
	t_env	*head;
	char	*str;

	head = lst;
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
	char	*env_var2;

	env_var = ft_strjoin(env_var, "=");
	env_var_cpy = ft_strdup(env_var);
	env_var2 = ft_strjoin(env_var, apres_egal);
	free(env_var);
	g_list = ft_modify_lst(g_list, env_var_cpy, env_var2);
	free(env_var_cpy);
	return (SUCCESS);
}

int	ft_built_in_export_add(char *env_var, char *apres_egal)
{
	char	*tmp;

	if (ft_strchr(apres_egal, '$'))
		apres_egal = ft_transform_dollar(apres_egal);
	if (ft_strchr(env_var, '$'))
		env_var = ft_transform_dollar(env_var);
	if (ft_check_variable_before_equal(env_var) == FAILURE
		|| ft_check_variable_after_equal(apres_egal) == FAILURE)
		return (FAILURE);
	if (ft_check_env_var_existence(env_var) == SUCCESS)
	{
		ft_built_in_export_modify(env_var, apres_egal);
		return (SUCCESS);
	}
	env_var = ft_strjoin(env_var, "=");
	tmp = env_var;
	env_var = ft_strjoin(env_var, apres_egal);
	free(tmp);
	ft_list_push_back(g_list, env_var);
	return (SUCCESS);
}

int	ft_built_in_export(char **cmd)
{
	char		*env_var;
	t_decompte	k;

	k.l = 0;
	if (cmd[1] == NULL)
		ft_built_in_env(cmd);
	else
	{
		while (cmd[++k.l])
		{	
			env_var = cmd[k.l];
			k.i = ft_find_the_equal(env_var);
			k.j = ft_find_where_is_equal(env_var);
			if (k.i == SUCCESS)
			{
				env_var[k.j] = 0;
				ft_built_in_export_add(env_var, env_var + k.j + 1);
			}
			if (k.i == FAILURE)
				printf("export: '%s': not a valid identifer\n", cmd[k.l]);
		}
	}
	return (SUCCESS);
}
