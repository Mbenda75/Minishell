/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 08:07:53 by adaloui           #+#    #+#             */
/*   Updated: 2022/03/03 17:09:21 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exit_shell(char *buffer, t_lst_cmd *lst)
{
	if (strcmp(buffer, "exit") == 0)
	{
		free(buffer);
		free_lst(lst);
		exit (0);
	}
}

t_lst_cmd	*init_shell(char *buffer, t_lst_cmd *lst)
{
	int		nb_pipe;
	
	nb_pipe = count_pipe(buffer);
	if (nb_pipe != 0)
	{
		/* parsing de plusieur commande */
	  	lst = create_lst(buffer, lst, nb_pipe);
		
	}
	else if (nb_pipe == 0)
	{
		printf("ici\n");
		lst = create_lst(buffer, lst, 0);
		/* parser une seul commande et execution*/
	}
	return (lst);
}

void	minishell(t_lst_cmd *lst, char **env)
{
	char	*promt_line;
	t_lst_cmd *mshell;
	char 	*new_line;

	mshell = NULL;
	while (1)
	{
		promt_line = readline("\033[0;33mSHELL DE MERDE\033[0;35m-> \033[0;37m");
		new_line = skip_quote_cmd(promt_line);
		add_history(promt_line);
		mshell = init_shell(new_line, lst);	
		free(new_line);
		exit_shell(promt_line, lst);
		free_lst(mshell);
		mshell = NULL;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_lst_cmd *lst;

	lst = NULL;
	//ft_signals();
	minishell(lst, env);
	return (0);
}