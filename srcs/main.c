/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 08:07:53 by adaloui           #+#    #+#             */
/*   Updated: 2022/03/03 20:04:01 by adaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

struct s_lst_cmd	*g_list;

int	exit_shell(char *buffer, t_lst_cmd *lst)
{
	if (strcmp(buffer, "exit") == 0)
	{
		free(buffer);
		free_lst(lst);
		exit (0);
	}
}

t_lst_cmd	*init_shell(char *buffer, t_lst_cmd *lst, char **env)
{
	int		nb_pipe;
	
	nb_pipe = count_pipe(buffer);
	if (nb_pipe != 0)
	{
		/* parsing de plusieur commande */
	  	lst = create_lst(buffer, lst, nb_pipe, env);
		
	}
	else if (nb_pipe == 0)
	{
		lst = create_lst(buffer, lst, 0, env);
		/* parser une seul commande et execution*/
	}
	return (lst);
}

void	minishell(t_lst_cmd *lst, char **env)
{
	t_lst_cmd *mshell;
	char *pwd;
	char 	*new_line;
	char 	*prompt_line;
	char **cmd = NULL;
	char **fake_env = NULL;
	mshell = NULL;

	fake_env = ft_env_cpy(env, fake_env);
	while (1)
	{
		pwd = getcwd(NULL, 0);
		prompt_line = readline(pwd);
		cmd = ft_split(prompt_line, ' ');
		free(pwd);
		if (cmd[0] == NULL)
			ft_putstr_fd(NULL, 0);
		if (cmd[0] != NULL)
		{
			new_line = skip_quote_cmd(prompt_line);
			add_history(prompt_line);
			mshell = init_shell(new_line, lst, env);
			free(new_line);
			if (ft_is_built_in(mshell->split_byspace[0]) == 1)
				exec_built_in(mshell->split_byspace, fake_env);
			else
				ft_putstr_fd("built-in introuvable\n", 0);
			exit_shell(prompt_line, mshell);
			free_lst(mshell);
			mshell = NULL;
		}
	}
}

int	main(int argc, char **argv, char **env)
{
	t_lst_cmd *lst;
	
/* 	if (!lst)
	{
		//ft_system_error();
		return (0);
	} */

 	lst = NULL;
	
	//ft_signals();
	minishell(lst, env);
	return (0);
}