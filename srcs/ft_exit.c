/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:09:23 by user42            #+#    #+#             */
/*   Updated: 2022/03/09 16:30:06 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_calc_exit_nb(char *cmd, int *i)
{
	long	lim;
	int		signe;

	lim = 0;
	while (*cmd == ' ' || *cmd == '\t' || *cmd == '\n')
		cmd++;
	if (*cmd == '-')
	{
		signe = -1;
		cmd++;
	}
	else
		signe = 1;
	while (*cmd >= '0' && *cmd <= '9')
	{
		lim = lim * 10 + (*cmd++ - 48);
		if ((lim > 2147483647 && signe == 1) || (lim > 2147483648 && signe == -1))
			return (-1);
	}
	if (*cmd)
		return (-1);
	*i = signe * lim;
	return (0);
}

int	ft_check_nb(char **cmd)
{
	int i;
	int j;

	i = 1;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			if (ft_isdigit(cmd[i][j]) == 1)
				return (FAILURE);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int	ft_check_nb_2(char *cmd)
{
	int i;

	i = 1;
	while (cmd[i])
	{
		if (ft_isdigit(cmd[i]) == 1)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

int	ft_check_exit_args()
{
	return (SUCCESS);
}

int ft_built_in_exit(char **cmd)
{
    int i;

    if (cmd[1] == NULL)
        i = 0;
	else if (ft_check_nb(cmd) == 0)
	{
		ft_putstr_fd("exit\n", 0);
		ft_putstr_fd("exit: numeric argument required\n", 0);
		free_env(g_list);
		exit (2);
	}
/*	else if (ft_check_nb_2(cmd[1]) == 1 && cmd[2])
	{
		ft_putstr_fd("exit\n", 0);
		ft_putstr_fd("exit: numeric argument required\n", 0);
		ft_free_charr(cmd);
		exit (2);
	}*/
	else if (ft_check_nb(cmd) == 1)
	{
		ft_putstr_fd("exit\n", 0);
		ft_putstr_fd("exit: numeric argument required\n", 0);
		free_env(g_list);
		exit (2);
	}
    else if (cmd[2])
	{
		ft_putstr_fd("exit\n", 2);
        ft_putstr_fd("exit: too many arguments\n", 0);
		free_env(g_list);
		exit (2);
	}
	else
    {
        if (ft_calc_exit_nb(cmd[1], &i))
			return (ft_custom_error("exit: bad number"));
    }
	free_env(g_list);
    printf("exit\n");
	exit(i);
}