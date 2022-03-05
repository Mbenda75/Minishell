/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 08:07:53 by adaloui           #+#    #+#             */
/*   Updated: 2022/03/05 20:12:31 by benmoham         ###   ########.fr       */
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

void	minishell(char **env)
{
	t_lst_cmd *parse_shell = NULL;
	t_init	*ishell = NULL;
	//t_pipex *pipex = NULL;
	char **env_2;

	ishell = malloc(sizeof(t_init));
	//pipex = malloc(sizeof(t_pipex));
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
			if (cmd == echo)
				parse_echo_arg(arg)
			if (cmd == other && multiquote = 1)
				cmd not found
			else if (cmd == other && multiquote == 0 && 1_quote == double)
				skip_dquote_cmd(cmd);
			else if (cmd == other && multiquote == 0 && 1_quote == simple)
				skip_squote_cmd(cmd);
				
			ishell->prompt_line = skip_dquote_cmd(ishell->prompt_line);
			//if (ishell->prompt_line[i] == 34)
			//else if (ishell->prompt_line[i] == 39)
				//ishell->prompt_line = skip_squote_cmd(ishell->prompt_line);
		
			add_history(ishell->prompt_line);
			parse_shell = init_shell(ishell->prompt_line, parse_shell, env);

/* 			pipex->index_path = search_path(env);
			pipex->split_path = ft_split(env[pipex->index_path], ':');
			pipex->path = boucle_path(pipex->split_path, parse_shell->split_byspace); 
			printf("path == %s", pipex->path);
 */
			free_str(ishell->cmd);
			free(ishell->prompt_line);
			
 			if (ft_is_built_in(parse_shell->split_byspace[0]) == 1)
				exec_built_in(parse_shell->split_byspace, env);
			else
				ft_putstr_fd("built-in introuvable\n", 0); 
			//free_str(pipex->split_path);
			free_lst(parse_shell);
			parse_shell = NULL;
			//free_lst(parse_shell);
		}
	}
}

int	main(int ac, char **av, char **env)
{
	t_env *env2;
	
	env2 = NULL;
	if (ac != 1 && !av)
		exit(1);
/* 	if (!lst)
	{
		//ft_system_error();
		return (0);
	} */
	//ft_signals()
	minishell(env);
	return (0);
}