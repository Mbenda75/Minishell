/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 18:51:40 by benmoham          #+#    #+#             */
/*   Updated: 2022/03/15 18:51:57 by benmoham         ###   ########.fr       */
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
	return (SUCCESS);
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
				|| (cmd[i] == '@' || cmd[i] == '%')))
			return (ft_custom_error("export: not valid identifier1\n"));
		i++;
	}
	return (0);
}

int	ft_check_variable_before_equal(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[0] >= '0' && cmd[0] <= '9')
		return (ft_custom_error("export: not valid identifier2\n"));
	while (cmd[i])
	{
		if (!((cmd[i] >= 'a' && cmd[i] <= 'z' )
				|| (cmd[i] >= 'A' && cmd[i] <= 'Z')
				|| (cmd[i] >= '0' && cmd[i] <= '9')
				|| (cmd[i] == '_' || cmd[i] == '=')))
			return (ft_custom_error("export: not valid identifier3\n"));
		i++;
	}
	return (0);
}
