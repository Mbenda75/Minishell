/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 18:51:40 by benmoham          #+#    #+#             */
/*   Updated: 2022/03/20 18:29:29 by adaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_find_the_equal(char *str)
{
	int	i;
	int	j;

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
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

int	ft_find_where_is_dollars(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (i);
		i++;
	}
	return (0);
}

int	ft_find_dollars(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (SUCCESS);
		i++;
	}
	return (FAILURE);
}

char	*ft_trim_name(char *cmd)
{
	char	*tmp;
	
	tmp = ft_strtrim(cmd, "+");
	return (tmp);
}

char *ft_add_env_var(char *after_equal, char *env_var)
{
	t_env *verify;
	t_env *env_value;
	char *new_after_equal;
	char **tab;
	char *tmp;
	char *tmp2;
	char *temp;
	int i = 0;
	char **split_bydollars;

	verify = g_list;
	env_value = g_list;
	split_bydollars == NULL;
	if (after_equal[0] == '$')
	{
		tmp2 = ft_strtrim(after_equal, "$");
		tmp = ft_strjoin(tmp2, "=");
	}
	else
	{
		split_bydollars = ft_split(after_equal, '$'); 
		tmp2 = ft_substr(after_equal, ft_find_where_is_dollars(after_equal) + 1, ft_strlen(after_equal)); // tpm = $USER
		tmp = ft_strjoin(tmp2, "=");
		i = 1;
	}
	free(tmp2);
	while (verify) 
	{
		if (ft_strncmp(verify->content, tmp, ft_strlen(tmp)) == SUCCESS)
			break ;
				verify = verify->next;
		if (verify == NULL && ft_strchr(after_equal, '$'))
		{
			printf("iciiiiiiii\n");
			free(tmp);
			if (i == 0)
				after_equal = ft_strdup("");
			else if (i == 1)
				after_equal = ft_strdup(split_bydollars[0]);
			if (i == 1)
				free_str(split_bydollars);
			return (after_equal);
		}
	}
	while (env_value)
	{
		if (ft_strncmp(env_value->content, tmp, ft_strlen(tmp)) == SUCCESS)
		{
			if (i == 1)
			{
				tmp2 = ft_substr(env_value->content, ft_find_where_is_equal(env_value->content) + 1, ft_strlen(env_value->content));
				new_after_equal = ft_strjoin(split_bydollars[0], tmp2);
				free(tmp2);
				free_str(split_bydollars);
				printf("ou ici\n");
				break ;
			}
			new_after_equal = ft_substr(env_value->content, ft_find_where_is_equal(env_value->content) + 1, ft_strlen(env_value->content));
			printf("sinon c la\n");
			break ;
		}
		env_value = env_value->next;
	}
	free(tmp);
	return (new_after_equal); 
}

int	ft_check_variable_after_equal(char *cmd)
{
	int	i;
	int	j;

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
				|| (cmd[i] == '@' || cmd[i] == '%')
				|| (cmd[i] == '\'' || cmd[i] == '"')))
			return (ft_custom_error("export: not valid identifier1"));
		i++;
	}
	return (0);
}

int	ft_check_variable_before_equal(char *cmd)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while(cmd[j])
		j++;
	if (cmd[j - 1] == '$')
		return (ft_custom_error("export: not valid identifier"));
	if (cmd[0] >= '0' && cmd[0] <= '9')
		return (ft_custom_error("export: not valid identifier2"));
	while (cmd[i])
	{
		if (!((cmd[i] >= 'a' && cmd[i] <= 'z' )
				|| (cmd[i] >= 'A' && cmd[i] <= 'Z')
				|| (cmd[i] >= '0' && cmd[i] <= '9')
				|| (cmd[i] == '_' || cmd[i] == '=')
				|| (cmd[i] == '$' || (cmd[j - 1] == '+' && cmd[j - 2] != '+')
				|| (cmd[i] == ' '))))
			return (ft_custom_error("export: not valid identifier3"));
		i++;
	}
	return (0);
}