/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 18:59:16 by user42            #+#    #+#             */
/*   Updated: 2022/03/22 20:30:42 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_print_several_dollars(char **split_bydollar, int k, int j, char *str)
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
			if (ft_checK_env_var_existence(split_bydollar[k]) == SUCCESS)
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

int ft_echo_several_dollars(char **cmd, int i, t_env *echo_env)
{
	int k;
	int j;
	char *str;
	char **split_bydollar;

	j = -1;
	while (cmd[i][++j] != '$')
		ft_putchar_fd(cmd[i][j], 1);
	k = -1;
	split_bydollar = ft_split(cmd[i], '$');
	ft_print_several_dollars(split_bydollar, k, j, str);
	ft_free_charr(split_bydollar);
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

void	ft_echo_print_single_dollar(char **split_bydollar)
{
	
}

int ft_echo_single_dollar(char **cmd, int i, t_env *echo_env)
{
	t_decompte j_et_s; // sert à sauter en cas de présence d'une écriture avant un dollar, on saute une case ex : echo popololo$user : jump sera égal à 1
	int j;
	char **split_bydollar;

	j = 0;
	j_et_s.l = 0; //jump à 0 dans le cas où y'a pas de caractère avant le $
	j_et_s.i = 0;
	j_et_s.j = 0;
	while (cmd[i][j] != '$')
	{
		ft_putchar_fd(cmd[i][j], 1);
		j_et_s.l = 1;
		j_et_s.j = 1;
		j++;
	}
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
	split_bydollar[j_et_s.l] == ft_strjoin(split_bydollar[j_et_s.l], "=");
	if (ft_checK_env_var_existence(split_bydollar[j_et_s.l]) == SUCCESS)
	{
		split_bydollar[j_et_s.l] = ft_change_dollar_var(split_bydollar[j_et_s.l]);
		ft_putstr_fd(split_bydollar[j_et_s.l], 1);
	}
	else
	{
		j_et_s.i = 1;
		ft_putstr_fd("", 1);
	}
	if ((cmd[i + 1] && j_et_s.i == 0) || (cmd[i + 1] && j_et_s.i == 1 && j_et_s.j == 1) )
		write(1, " ", 1);
	return (SUCCESS);
}
