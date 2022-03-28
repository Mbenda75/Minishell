/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 08:27:34 by adaloui           #+#    #+#             */
/*   Updated: 2022/03/28 22:39:31 by adaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_signals_handler(int signal)
{
	char	*ishell;

	ishell = NULL;
	if (signal == SIGQUIT)
		rl_replace_line("", 0);
	if (signal == SIGINT)
	{
		ft_putstr_fd("\n", 0);
		ishell = getcwd(NULL, 0);
		rl_replace_line("", 0);
		printf("%s ", ishell);
		free(ishell);
		g_list->exit_value = 130;
	}
	/*if (signal == SIGSEGV)
	{
		ft_putstr_fd("\nexit\n", 0);
		exit(0);
	}*/
}

void	ft_signals(void)
{
	signal(SIGINT, ft_signals_handler);
	signal(SIGSEGV, ft_signals_handler);
	signal(SIGQUIT, SIG_IGN);
}
