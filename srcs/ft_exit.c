/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:09:23 by user42            #+#    #+#             */
/*   Updated: 2022/03/03 16:14:02 by adaloui          ###   ########.fr       */
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

int	ft_check_exit_args(char **cmd)
{
	return (SUCCESS);
}

int ft_built_in_exit(char **cmd, char **envp)
{
    int i;
    int j;

    j = 0;
    if (cmd[1] == NULL)
        i = 0;
	else if (ft_check_nb(cmd) == 1)
	{
		ft_putstr_fd("exit: numeric argument required\n", 0);
		ft_free_charr(cmd);
		exit (2);
	}
    else if (cmd[2])
	{
        ft_putstr_fd("exit: too many arguments\n", 0);
		ft_free_charr(cmd);
		exit (2);
	}
    else
    {
        if (ft_calc_exit_nb(cmd[1], &i))
			return (ft_custom_error("exit: bad number"));
    }
    ft_free_charr(cmd);
/*    while (j <= 150)
    {
        close(j);
        j++;
    }*/

    printf("exit\n");
	exit(i);
}