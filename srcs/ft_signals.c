/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 08:27:34 by adaloui           #+#    #+#             */
/*   Updated: 2022/03/20 02:25:22 by adaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_signals_handler(int signal)
{
	int		i;
	char	*ishell;

	i = 0;
	ishell = NULL;
	if (signal == SIGQUIT)
		rl_replace_line("", 0);
	if (signal == SIGINT)
	{
		ft_putstr_fd("\n", 0);
		ishell = getcwd(NULL, 0);
		printf("%s", ishell);
		free(ishell);
	}
	if (signal == SIGSEGV)
	{
		ft_putstr_fd("\nexit ctrl d\n", 0);
		exit(EXIT_FAILURE);
	}
}

void	ft_signals()
{
	signal(SIGINT, ft_signals_handler);
	//signal(SIGSEGV, ft_signals_handler);
	signal(SIGQUIT, SIG_IGN);
}
