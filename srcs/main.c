/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 08:07:53 by adaloui           #+#    #+#             */
/*   Updated: 2022/03/04 18:23:56 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

struct s_lst_cmd	*g_list;

int count_pipe(char *str)
{
	int i;
	int pipe;

	i = 0;
	pipe = 0;
	while(str[i])
	{
		if (str[i] == '|')
			pipe++;
		i++;
	}
	return (pipe);
}

t_lst_cmd	*init_shell(char *buffer, t_lst_cmd *lst, char **env)
{
	int		nb_pipe;
	
	nb_pipe = count_pipe(buffer);
	if (nb_pipe != 0)
	{
		/* parsing de plusieur commande */
	  	lst = create_lst(buffer, nb_pipe, lst, env);
		
	}
	else if (nb_pipe == 0)
	{
		lst = create_lst(buffer, 0, lst, env);
		/* parser une seul commande et execution*/
	}
	return (lst);
}


void	minishell(char **env)
{
	t_lst_cmd *mshell = NULL;
	t_init	*ishell = NULL;

	ishell = malloc(sizeof(t_init));
	while (1)
	{
		ishell->pwd = getcwd(NULL, 0);
		ishell->prompt_line = readline(ishell->pwd);
		ishell->cmd = ft_split(ishell->prompt_line, ' ');
		free(ishell->pwd);
		if (ishell->cmd[0] == NULL)
			ft_putstr_fd(NULL, 0);
		if (ishell->cmd[0] != NULL)
		{
			ishell->new_line = skip_dquote_cmd(ishell->prompt_line);
			add_history(ishell->prompt_line);
			mshell = init_shell(ishell->new_line, mshell, env);
			free(ishell->new_line);
			free_str(ishell->cmd);
			free(ishell->prompt_line);
			if (ft_is_built_in(mshell->split_byspace[0]) == 1)
				exec_built_in(mshell->split_byspace, env);
			else
				ft_putstr_fd("built-in introuvable\n", 0);
			free_lst(mshell);
			mshell = NULL;
			//free_lst(mshell);
		}
	}
}

int	main(int ac, char **av, char **env)
{
	g_list = NULL;
	if (ac != 1 && !av)
		exit(1);
	
/* 	if (!lst)
	{
		//ft_system_error();
		return (0);
	} */
	
	//ft_signals()
	g_list = malloc(sizeof(t_lst_cmd));
	minishell(env);
	return (0);
}