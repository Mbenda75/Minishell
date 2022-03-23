/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 18:59:16 by user42            #+#    #+#             */
/*   Updated: 2022/03/23 16:53:50 by adaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_print_several_dollars(char **split_bydollar, int k, int j, char *str)
{
	while (split_bydollar[++k])
	{
		if (ft_strchr(split_bydollar[k], '?'))
		{
			j = 1;
			ft_putnbr_fd(g_list->exit_value, 1);
			while (split_bydollar[k][j])
			{
				ft_putchar_fd(split_bydollar[k][j], 1);
				j++;
			}
		}
		else
		{
			if (ft_check_env_var_existence(split_bydollar[k]) == SUCCESS)
			{
				str = ft_change_dollar_var(split_bydollar[k]);
				ft_putstr_fd(str, 1);
				free(str);
			}
			else
				ft_putstr_fd("", 1);
		}
	}
}

int	ft_echo_several_dollars(char **cmd, int i, t_env *echo_env)
{
	int		k;
	int		j;
	char	*str;
	char	**split_bydollar;

	j = -1;
	while (cmd[i][++j] != '$')
		ft_putchar_fd(cmd[i][j], 1);
	k = -1;
	split_bydollar = ft_split(cmd[i], '$');
	ft_print_several_dollars(split_bydollar, k, j, str);
	free_str(split_bydollar);
	j = 0;
	j = ft_strlen(cmd[i]) - 1;
	if (cmd[i][j - 1] == '$')
	{
		ft_putstr_fd("$", 1);
		if (cmd[i + 1])
			write(1, " ", 1);
		return (SUCCESS);
	}
	if (cmd[i + 1])
		write(1, " ", 1);
	return (SUCCESS);
}

t_decompte	ft_echo_print_single_dollar(char **cmd, int i,
		char **split_bydollar, t_decompte j_et_s)
{
	char	*str;

	if (ft_check_env_var_existence(split_bydollar[j_et_s.l]) == SUCCESS)
	{
		str = ft_change_dollar_var(split_bydollar[j_et_s.l]);
		ft_putstr_fd(str, 1);
		free(str);
	}
	else
	{
		j_et_s.i = 1; // on ne doit pas ecrire d'espace
		ft_putstr_fd("", 1);
	}
	return (j_et_s);
}

t_decompte	ft_init_and_write(char **cmd, int i, t_decompte j_et_s)
{
	int	j;

	j = 0;
	j_et_s.l = 0;
	j_et_s.j = 0;
	while (cmd[i][j] != '$')
	{
		ft_putchar_fd(cmd[i][j], 1);
		j_et_s.l = 1; // on met a 1 pour pourvoir a'occuper d'un eventuel $? qui sera split et mis dans la case [i] = 1
		j_et_s.j = 1; // espace_2 pour faire des sauts quans la variable est fausse
		j++;
	}
//	j = ft_strlen(cmd[i]) - 1;
/*	if (cmd[i][j] == '$')
	{
		ft_putstr_fd("$", 1);
		if (cmd[i + 1])
			write(1, " ", 1);
		//return (j_et_s);
	}*/
	return (j_et_s);
}

int	ft_echo_single_dollar(char **cmd, int i, t_env *echo_env)
{
	t_decompte	j_et_s;
	int			j;
	char		**split_bydollar;

	j_et_s = ft_init_and_write(cmd, i, j_et_s);
	j = ft_strlen(cmd[i]) - 1;
	if (cmd[i][j] == '$')
	{
		ft_putstr_fd("$", 1);
		if (cmd[i + 1])
			write(1, " ", 1);
		return (SUCCESS);
	}
	split_bydollar = ft_split(cmd[i], '$');
	if (ft_strchr(split_bydollar[j_et_s.l], '?'))
	{
		j = 1;
		ft_putnbr_fd(g_list->exit_value, 1);
		while (split_bydollar[j_et_s.l][j])
		{
			ft_putchar_fd(split_bydollar[j_et_s.l][j], 1);
			j++;
		}
		if (cmd[i + 1])
			write(1, " ", 1);
		return (SUCCESS);
	}
	j_et_s = ft_echo_print_single_dollar(cmd, i, split_bydollar, j_et_s);
	free_str(split_bydollar);
	if ((cmd[i + 1] && j_et_s.i == 0) // il y'a un autre *cmd apres et la variable inscrite est bonne
		|| (cmd[i + 1] && j_et_s.i == 1 && j_et_s.j == 1)) //il y'a un autre *cmd , la variable est fausse  
		write(1, " ", 1);
	return (SUCCESS);
}
