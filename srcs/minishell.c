/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 15:46:47 by benmoham          #+#    #+#             */
/*   Updated: 2022/03/22 20:04:43 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	start_minishell(t_init ishell, char **env)
{
	t_lst_cmd	*mshell;
	t_lst_cmd	*tmp;
	int i;
	
	i = -1;
	mshell = NULL;
	mshell = init_shell(ishell.new_line, mshell);
	tmp = mshell;
	while (tmp)
	{
		if (ft_is_built_in(mshell->split_byspace[0]) == 1)
			exec_built_in(mshell, env);
		else
			cmd_fork(tmp, env, ++i);
		tmp = tmp->next;
	}
	close_wait(ishell, mshell);
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

void	*init_pfd(t_init ishell)
{
	int i;
	g_list->nb_pipe = count_pipe(ishell.new_line);
	printf("nb pipe %d\n", g_list->nb_pipe);
	if (g_list->nb_pipe != 0)
	{
		i = -1;
		g_list->pfd = NULL;
		g_list->pfd = malloc(sizeof(int **) * g_list->nb_pipe);
		if (!g_list->pfd)
			return (NULL);
		while(++i < g_list->nb_pipe)
		{
			printf("nb de pfd\n");
			g_list->pfd[i] = malloc(sizeof(int) * 2);
			if (!g_list->pfd)
				return (NULL);
		}
		i = -1;
		while (++i < g_list->nb_pipe)
			pipe(g_list->pfd[i]);
	}
}

void	minishell(char **env)
{
	t_init	ishell;
	int i;

	i = -1;
	memset(&g_list, 0, sizeof(g_list));
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
			ishell.new_line = skip_quote(ishell.prompt_line);
			add_history(ishell.prompt_line);
			if (check_pipe(ishell.new_line) == 1)
			{
				printf("error pipe\n");
				free(ishell.new_line);
				free_str(ishell.cmd);
				free(ishell.prompt_line);
			}
			else
			{
				init_pfd(ishell);
				start_minishell(ishell, env);
				if(g_list->nb_pipe != 0)
					free_fd(g_list->pfd);
			}
		}
	}
}
