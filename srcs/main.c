/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 08:07:53 by adaloui           #+#    #+#             */
/*   Updated: 2022/03/02 17:40:56 by benmoham         ###   ########.fr       */
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

t_lst_cmd	*parsing_shell(char *buffer, t_lst_cmd *lst)
{
	int		nb_pipe;
	char 	*stock;

	stock = skip_dquote(buffer);
	printf("%s\n" ,stock);
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
	free(stock);
	return (lst);
}

void	minishell(t_lst_cmd *lst, char **env)
{
	char	*buffer;
	t_lst_cmd *mshell;
	
	mshell = NULL;
	while (1)
	{
		buffer = readline("\033[0;33mSHELL DE MERDE\033[0;35m-> \033[0;37m"); 
		add_history(buffer);
		mshell = parsing_shell(buffer, lst);
		
		
		exit_shell(buffer, lst);
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