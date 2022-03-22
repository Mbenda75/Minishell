/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 15:46:47 by benmoham          #+#    #+#             */
/*   Updated: 2022/03/22 16:30:40 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	start_minishell(t_init ishell, char **env)
{
	t_lst_cmd	*mshell;
	t_lst_cmd	*tmp;
	int i;

	mshell = NULL;
	mshell = init_shell(ishell.new_line, mshell);
	tmp = mshell;
	/*			EXEC PART & BUILTINS			*/
	while (tmp)
	{
	//	printf("tmpl == %s\n", tmp->split_byspace[0]);
		g_list->exit_value = builtin_or_exec(tmp, env, ishell);

		//printf("exit__value = %d\n", g_list->exit_value);
		tmp = tmp->next;

	}
	free_lst(mshell);
	free(ishell.new_line);
	free_str(ishell.cmd);
	free(ishell.prompt_line);
}

char *get_prompt(void)
{
	char *tmp;
	char *ret;

	tmp = getcwd(NULL, 0);
	ret = ft_strjoin(tmp, " ");
	free(tmp);
	return (ret);	
}

void	minishell(char **env)
{
	t_init	ishell;

	g_list = cpy_env(env);
	while (1)
	{
		ishell.pwd = get_prompt();
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
			ishell.new_line = skip_quote(ishell.prompt_line);
			//if (ft_find_dollars(ishell.new_line) == SUCCESS)
			//	ishell.new_line = ft_transform_dollar(ishell.new_line);
			printf("\033[0;32mishell.new_line = %s\n\033[0;37m", ishell.new_line);
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
