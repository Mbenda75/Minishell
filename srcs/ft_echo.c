/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 22:01:53 by benmoham          #+#    #+#             */
/*   Updated: 2022/03/20 22:16:30 by adaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_option(char *str)
{
	int	i;
  
	i = 0;
	while (str[i])
	{
		if (i == 0 && (str[i] != '-'))
			return (0);
		if (i > 0 && (str[i] != 'n'))
			return (0);
		i++;
	}
	if (i <= 1)
		return (0);
	return (1);
}

int	ft_len(char *cmd[])
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

int ft_count_dollars(char **cmd, int i)
{
	int dollar;
	int j;

	dollar = 0;
	j = 0;
	while (cmd[i][j])
	{
		if (cmd[i][j] == '$')
			dollar++;
		j++;
	}
	return (dollar);
}

int ft_echo_several_dollars(char **cmd, int i, t_env *echo_env)
{
	int k;
	char **split_bydollar;

	k = -1;
	while (cmd[i][++k] != '$')
		ft_putchar_fd(cmd[i][k], 1);
	k = 0;
	split_bydollar = ft_split(cmd[i], '$');
	while (split_bydollar[k])
	{
		if (ft_checK_env_var_existence(split_bydollar[k]) == SUCCESS)
		{
			split_bydollar[k] = ft_change_dollar_var(split_bydollar[k]);
			ft_putstr_fd(split_bydollar[k], 1);
		}
		else
			ft_putstr_fd("", 1);
		k++;
	}
	if (cmd[i + 1])
		write(1, " ", 1);
	ft_free_charr(split_bydollar);
	return (SUCCESS);
}

int ft_echo_single_dollar(char **cmd, int i, t_env *echo_env)
{
	int jump;
	int j;
	int space;
	int space_2;
	char **split_bydollar;

	j = 0;
	jump = 0;
	space = 0;
	space_2 = 0;
	while (cmd[i][j] != '$')
	{
		ft_putchar_fd(cmd[i][j], 1);
		jump = 1;
		space_2 = 1;
		j++;
	}
	split_bydollar = ft_split(cmd[i], '$');
	split_bydollar[jump] == ft_strjoin(split_bydollar[jump], "=");
	if (ft_checK_env_var_existence(split_bydollar[jump]) == SUCCESS)
	{
		split_bydollar[jump] = ft_change_dollar_var(split_bydollar[jump]);
		ft_putstr_fd(split_bydollar[jump], 1);
	}
	else
	{
		space = 1;
		ft_putstr_fd("", 1);
	}
	if ((cmd[i + 1] && space == 0) || (cmd[i + 1] && space == 1 && space_2 == 1) )
		write(1, " ", 1);
	return (SUCCESS);
}


int	ft_echo_dollar(char	**cmd, int i, int j)
{
	t_env	*echo_env;
	int dollar = 0;

	echo_env = g_list;
	dollar = ft_count_dollars(cmd, i);
	if (dollar == 1)
	{
		ft_echo_single_dollar(cmd, i, echo_env);
		return (SUCCESS);
	}
	if (dollar > 1)
	{
		ft_echo_several_dollars(cmd, i, echo_env);
		return (SUCCESS);
	}
}

int	ft_built_echo(char *cmd[])
{
	t_decompte	m;
	char		*tmp;

	m.i = 1;
	m.l = 0;
	m.j = 0;
	if (ft_len(cmd) != 1)
	{
		while (cmd[m.i] && check_option(cmd[m.i]))
		{
			m.l = 1;
			m.i++;
		}
		while (cmd[m.i])
		{
			m.j = 0;
			while (cmd[m.i][m.j])
			{
				if (ft_find_dollars(cmd[m.i]) == SUCCESS)
				{
					m.j++;
					ft_echo_dollar(cmd, m.i, m.j);
					break ;
				}
				else
				{
					ft_putstr_fd(cmd[m.i], 1);
					if (cmd[m.i + 1])
						write(1, " ", 1);
					break ;
				}
			m.j++;
			}
		m.i++;
		}
	}
	if (!m.l)
		write(1, "\n", 1);
	return (0);
}