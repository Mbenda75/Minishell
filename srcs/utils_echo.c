/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 18:59:16 by user42            #+#    #+#             */
/*   Updated: 2022/03/27 23:54:07 by adaloui          ###   ########.fr       */
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
			ft_putnbr_fd(g_list->exit_value, STDOUT_FILENO);
			while (split_bydollar[k][j])
			{
				ft_putchar_fd(split_bydollar[k][j], STDOUT_FILENO);
				j++;
			}
		}
		else
		{
			if (ft_check_env_var_existence(split_bydollar[k]) == SUCCESS)
			{
				str = ft_change_dollar_var(split_bydollar[k]);
				ft_putstr_fd(str, STDOUT_FILENO);
				free(str);
			}
			else
				ft_putstr_fd("", STDOUT_FILENO);
		}
	}
}

int	ft_echo_several_dollars(char **cmd, int i)
{
	int		k;
	int		j;
	char	*str;
	char	**split_bydollar;

	j = -1;
	str = NULL;
	while (cmd[i][++j] != '$')
		ft_putchar_fd(cmd[i][j], STDOUT_FILENO);
	k = -1;
	split_bydollar = ft_split(cmd[i], '$');
	ft_print_several_dollars(split_bydollar, k, j, str);
	free_str(split_bydollar);
	j = 0;
	j = ft_strlen(cmd[i]) - 1;
	if (cmd[i][j - 1] == '$')
	{
		ft_putstr_fd("$", STDOUT_FILENO);
		if (cmd[i + 1])
			write(STDOUT_FILENO, " ", 1);
		return (SUCCESS);
	}
	if (cmd[i + 1])
		write(STDOUT_FILENO, " ", 1);
	return (SUCCESS);
}

int	ft_echo_single_dollar(char **cmd, int i)
{
	t_decompte	j_et_s;
	t_decompte	i_et_j;
	char		**s_bydollar;

	i_et_j.i = i;
	j_et_s = ft_init_and_write(cmd, i, j_et_s);
	i_et_j.j = ft_strlen(cmd[i_et_j.i]) - 1;
	if (cmd[i_et_j.i][i_et_j.j] == '$')
	{
		ft_putstr_fd("$", STDOUT_FILENO);
		if (cmd[i_et_j.i + 1])
			write(STDOUT_FILENO, " ", 1);
		return (SUCCESS);
	}
	s_bydollar = ft_split(cmd[i_et_j.i], '$');
	if (ft_print_exit_value(cmd, &j_et_s, &i_et_j, s_bydollar) == SUCCESS)
		return (SUCCESS);
	j_et_s = ft_echo_print_single_dollar(s_bydollar, j_et_s);
	free_str(s_bydollar);
	if ((cmd[i_et_j.i + 1] && j_et_s.i == 0)
		|| (cmd[i_et_j.i + 1] && j_et_s.i == 1 && j_et_s.j == 1))
		write(STDOUT_FILENO, " ", 1);
	return (SUCCESS);
}
