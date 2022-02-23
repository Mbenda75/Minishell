/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 08:27:34 by adaloui           #+#    #+#             */
/*   Updated: 2022/02/23 15:16:23 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_signals_handler(int signal)
{
	int i;

	i = 0;
	if (signal == SIGQUIT)
		rl_replace_line("", 0);
	if (signal == SIGINT)
	{
		ft_putstr_fd("\n", 0);
		ft_putstr_fd("\033[0;33madaloui\033[0;35m42->\033[0;37m", 0);
	}
	if (signal == SIGSEGV)
	{
		ft_putstr_fd("\nexit\n", 0);
	 	while (i <= 150)
		{
			close(i);
			i++;
		}
		exit(EXIT_FAILURE);
	}
}

void	ft_signals()
{
	signal(SIGINT, ft_signals_handler);
	signal(SIGSEGV, ft_signals_handler);
	signal(SIGQUIT, SIG_IGN);
}
