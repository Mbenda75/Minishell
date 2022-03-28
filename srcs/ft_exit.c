/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:09:23 by user42            #+#    #+#             */
/*   Updated: 2022/03/28 19:08:57 by adaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_skip_whitespaces(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] == ' ' || cmd[i] == '\t' || cmd[i] == '\n')
		i++;
	return (i);
}

int	ft_check_signs(char *cmd, int i, int sign)
{
	if (cmd[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (cmd[i] == '+')
	{
		sign = 1;
		i++;
	}
	else
		sign = 1;
	return (sign);
}

int	ft_calc_exit_nb(char *cmd, int *exit_value)
{
	int					i;
	int					sign;
	unsigned long long	lim;

	lim = 0;
	sign = 0;
	i = ft_skip_whitespaces(cmd);
	if (cmd[i] == '-' || cmd[i] == '+')
	{
		sign = ft_check_signs(cmd, i, sign);
		i++;
	}
	while (cmd[i] >= '0' && cmd[i] <= '9')
	{
		lim = lim * 10 + (cmd[i] - 48);
		if ((lim > __LONG_LONG_MAX__ && sign == 1)
			|| (lim > __LONG_LONG_MAX__ && sign == -1))
			return (FAILURE);
		i++;
	}
	if (cmd[i] != '\0')
		return (FAILURE);
	*exit_value = sign * lim;
	return (SUCCESS);
}

void	ft_free_lst_print_and_exit(t_lst_cmd *mshell, int exit_value)
{
	free_env(g_list);
	free_lst(mshell);
	exit(exit_value);
}

int	ft_built_in_exit(t_lst_cmd *mshell)
{
	int	exit_value;

	if (mshell->split_byspace[1] == NULL)
		exit_value = 0;
	else if (mshell->split_byspace[2] != NULL)
	{
		if (ft_calc_exit_nb(mshell->split_byspace[1], &exit_value) == FAILURE)
		{
			printf("exit\nminishell: exit: numeric argument required\n");
			exit_value = 2;
		}
		else
			return (ft_custom_error("exit\nexit: too many arguments"));
	}
	else if (ft_calc_exit_nb(mshell->split_byspace[1], &exit_value) == FAILURE)
	{
		printf("exit\nminishell: exit: numeric argument required\n");
		exit_value = 2;
	}
	else
		printf("exit\n");
	ft_free_lst_print_and_exit(mshell, exit_value);
	return (SUCCESS);
}
