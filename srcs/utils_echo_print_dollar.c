/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_echo_print_dollar.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 23:54:12 by adaloui           #+#    #+#             */
/*   Updated: 2022/03/27 23:56:43 by adaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_decompte	ft_echo_print_single_dollar(char **split_bydollar,
	t_decompte j_et_s)
{
	char	*str;

	if (ft_check_env_var_existence(split_bydollar[j_et_s.l]) == SUCCESS)
	{
		str = ft_change_dollar_var(split_bydollar[j_et_s.l]);
		ft_putstr_fd(str, STDOUT_FILENO);
		free(str);
	}
	else
	{
		j_et_s.i = 1;
		ft_putstr_fd("", STDOUT_FILENO);
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
		ft_putchar_fd(cmd[i][j], STDOUT_FILENO);
		j_et_s.l = 1;
		j_et_s.j = 1;
		j++;
	}
	return (j_et_s);
}

int	ft_print_exit_value(char **cmd, t_decompte *j_et_s, t_decompte *i_et_j,
	char **s_bydollar)
{
	if (ft_strchr(s_bydollar[j_et_s->l], '?'))
	{
		i_et_j->j = 1;
		ft_putnbr_fd(g_list->exit_value, STDOUT_FILENO);
		while (s_bydollar[j_et_s->l][i_et_j->j])
		{
			ft_putchar_fd(s_bydollar[j_et_s->l][i_et_j->j], STDOUT_FILENO);
			i_et_j->j++;
		}
		if (cmd[i_et_j->i + 1])
			write(STDOUT_FILENO, " ", 1);
		return (SUCCESS);
	}
	return (FAILURE);
}
