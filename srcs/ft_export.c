/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 17:40:02 by user42            #+#    #+#             */
/*   Updated: 2022/03/09 23:59:21 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_find_the_equal(char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i])
		i++;
	while (str[j])
	{
		if (str[i - 1] == '=' && str[j] == '=')
			return (0);
		j++;
	}
	if (str[i - 1] == '=')
			return (2);
	i = 0;
	while (str[i])
	{
		if (str[0] == '=')
			return (FAILURE);
		if (str[i] == '=' && i != 0)
			return (SUCCESS);
		i++;
	}
	return (FAILURE);
}

int	ft_find_where_is_equal(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (SUCCESS);
}

int	ft_check_variable_after_equal(char *cmd)
{
	int i;
	int j;

	i = 0;
	while (cmd[i])
	{
			if (!((cmd[i] >= 'a' && cmd[i] <= 'z' )
				|| (cmd[i] >= 'A' && cmd[i] <= 'Z')
				|| (cmd[i] >= '0' && cmd[i] <= '9')
				|| (cmd[i] == '_' || cmd[i] == '=')
				|| (cmd[i] == '+' || cmd[i] == '*')
				|| (cmd[i] == '-' || cmd[i] == '.')
				|| (cmd[i] == '$' || cmd[i] == '^')
				|| (cmd[i] == '?' || cmd[i] == ',')
				|| (cmd[i] == '-' || cmd[i] == '{')
				|| (cmd[i] == '}' || cmd[i] == '[')
				|| (cmd[i] == ']' || cmd[i] == '#')
				|| (cmd[i] == '~' || cmd[i] == '/')
				|| (cmd[i] == '@' || cmd[i] == '%')))
			return (ft_custom_error("export: not valid identifier\n"));
		i++;
	}
	return (0);
}

int	ft_check_variable_before_equal(char *cmd)
{
	int i;

	i = 0;
	if (cmd[0] >= '0' && cmd[0] <= '9')
		return (ft_custom_error("export: not valid identifier\n"));
	while (cmd[i])
	{
			if (!((cmd[i] >= 'a' && cmd[i] <= 'z' )
				|| (cmd[i] >= 'A' && cmd[i] <= 'Z')
				
				|| (cmd[i] == '_' || cmd[i] == '=')))
			return (ft_custom_error("export: not valid identifier\n"));
		i++;
	}
	return (0);
}

t_env    *ft_list_push_back(t_env *cpy_env, char *str)
{
    t_env    *list;
	int i;

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
		printf("i push bacl = %d\n", i);
        list->next = file_env(str, i);
    }
    return (list);
}

t_env *ft_modify_lst(t_env *lst, char *env_var_cpy, char *env_var)
{
	t_env *head;
	t_env *tail;
	char *str;

	head = lst;
	tail = head;
	str = ft_strjoin(env_var_cpy, "=");
	while (head != NULL)
	{
		if (ft_strncmp(head->content, str, ft_strlen(env_var_cpy)) == 0)
		{
			head->content = env_var;
			break ;
		}
		head = head->next;
	}
	if (head == NULL)
		head = ft_list_push_back(lst, env_var);
	printf("adrress mdy list == %p\n", env_var);
	free(str);
	return (lst);
}

int	ft_built_in_export_modify(char *env_var, char *apres_egal)
{
	char  *env_var_cpy;
	char *tmp;
	char *env_var2;
	
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
		env_var2 = ft_strjoin(env_var, apres_egal);
		free(env_var);
		g_list = ft_modify_lst(g_list, env_var_cpy, env_var2);
		free(env_var_cpy);
	}
	return (SUCCESS);
}

int	ft_built_in_export_add(char *env_var, char *apres_egal)
{
	t_env *head;
	t_env *tail;
	char *tmp;
	
	if (ft_check_variable_before_equal(env_var) == 1)
		return (FAILURE);
	if (ft_check_variable_after_equal(apres_egal) == 1)
		return (FAILURE);
	head = g_list;
	tail = head;
	while (head != NULL)
	{
		if (ft_strncmp(head->content, env_var, ft_strlen(env_var)) == 0)
		{
			ft_built_in_export_modify(env_var, apres_egal);
			return (SUCCESS);
		}
		head = head->next;
	}
	if (ft_strchr(env_var, '='))
		env_var = ft_strjoin(env_var, apres_egal);
	else
	{
		env_var = ft_strjoin(env_var, "=");
		tmp = env_var;
		env_var = ft_strjoin(env_var, apres_egal);
		free(tmp);
	}
	tail = ft_list_push_back(g_list, env_var);
	return (SUCCESS);
}

int	ft_built_in_export(char **cmd)
{
	char *env_var;
	char temp;
	t_decompte k;

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
			if (k.i == 1)
			{
				return (FAILURE);
			}
		}
	}
	return (SUCCESS);
}