/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 08:07:53 by adaloui           #+#    #+#             */
/*   Updated: 2022/03/11 19:16:10 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

struct s_env	*g_list;

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
	t_redirection *red;
	
	red = ft_count_simple_redirect(buffer);
	free(red);
	nb_pipe = count_pipe(buffer);
	//printf("red_norm %d\nred_inv %d\ndb_red_n%d\ndb_ezs_inv%d\n", red->redirection_normal, red->redirection_inverse, red->double_red_norm, red->double_red_inv);
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
	t_init	ishell;
	t_pipex *pipex = NULL;
	int	pfd[2];
	int i = 0;
	//ishell = malloc(sizeof(t_init));
	pipex = malloc(sizeof(t_pipex));
	g_list = cpy_env(env);
	while (1)
	{
		ishell.pwd = getcwd(NULL, 0);
		ishell.prompt_line = readline(ishell.pwd);
		ishell.cmd = ft_split(ishell.prompt_line, ' ');
		free(ishell.pwd);
		if (ishell.cmd[0] == NULL)
		{
			ft_putstr_fd(NULL, 0);
			free_str(ishell.cmd);
		}
		else if (ishell.cmd[0] != NULL)
		{
			/*			PARSING NOT FINISH 				*/
			ishell.new_line = skip_dquote_cmd(ishell.prompt_line);
			add_history(ishell.prompt_line);
			mshell = init_shell(ishell.new_line, mshell, env);
	
			free(ishell.new_line);
			free_str(ishell.cmd);
			free(ishell.prompt_line);
			
			/*			EXEC PART					*/
			if (start_exec(pipex, mshell, env) == 0)
				printf("out\n");
			else
			{
			/*		BUILTIN PART					*/
		 		if (ft_is_built_in(mshell->split_byspace[0]) == 1)
					exec_built_in(mshell->split_byspace, env);
				else
					ft_putstr_fd("built-in introuvable\n", 0);
			}
			free_lst(mshell);
			pipex->line_path = NULL;
			mshell = NULL;
		}
	}
}

int	main(int ac, char **av, char **env)
{
	if (ac != 1 && !av)
		exit(1);
/* 	if (!lst)
	{
		//ft_system_error();
		return (0);
	}*/
	//ft_signals();
	minishell(env);
	return (0);
}