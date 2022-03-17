/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 15:46:47 by benmoham          #+#    #+#             */
/*   Updated: 2022/03/17 14:02:58 by adaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	start_minishell(t_init ishell, char **env)
{
	t_lst_cmd	*mshell;
	t_lst_cmd	*tmp;

	mshell = NULL;
	mshell = init_shell(ishell.new_line, mshell);
	tmp = mshell;
	/*			EXEC PART & BUILTINS			*/
	while (tmp)
	{
		//printf("tmpl == %s\n", tmp->split_byspace[0]);
		builtin_or_exec(tmp, env, ishell);
		tmp = tmp->next;
	}
	free_lst(mshell);
	free(ishell.new_line);
	free_str(ishell.cmd);
	free(ishell.prompt_line);
}

void	minishell(char **env)
{
	t_init	ishell;

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
			if (check_first_quote(ishell.prompt_line) == 1)
				ishell.new_line = skip_quote(ishell.prompt_line);
			else if (check_first_quote(ishell.prompt_line) == 2)
				ishell.new_line = skip_quote(ishell.prompt_line);
			else if (check_first_quote(ishell.prompt_line) == 0)
				ishell.new_line = ft_strdup(ishell.prompt_line);
			add_history(ishell.prompt_line);
			//pipex->nb_cmd = count_pipe(ishell.new_line);
			if (check_pipe(ishell.new_line) == 1)
			{
				printf("error pipe\n");
				free(ishell.new_line);
				free_str(ishell.cmd);
				free(ishell.prompt_line);
			}
			else
				start_minishell(ishell, env);
		}
	}
}
