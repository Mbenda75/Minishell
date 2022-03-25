/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 18:51:40 by benmoham          #+#    #+#             */
/*   Updated: 2022/03/25 17:32:42 by adaloui          ###   ########.fr       */
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
			return (SUCCESS);
		j++;
	}
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

int	ft_check_variable_after_equal(char *cmd)
{
	int	i;

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
	if (cmd[0] == '\0')
		return(ft_custom_error("export: not valid identifier1"));
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
				|| (cmd[i] == '_' || cmd[i] == '$') 
				|| (cmd[j - 1] == '+' && cmd[j - 2] != '+')
				|| (cmd[i] == ' ' || cmd[i] == '=')))
			return (ft_custom_error("export: not valid identifier3"));
		i++;
	}
	return (0);
}