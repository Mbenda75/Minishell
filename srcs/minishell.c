/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 15:46:47 by benmoham          #+#    #+#             */
/*   Updated: 2022/03/21 20:23:59 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


 void	cmd(t_lst_cmd *tmp, char **env, int i)
{
	int k;
	int l;

	k = -1;
	tmp->pipex->child = fork();
	
	if (tmp->pipex->child == -1)
	{
		write(2, "fork failed\n", 13);
		exit (1);
	}
	if (tmp->pipex->child == 0)
	{
		if (i != 0) //pour dup notre entre standart dans les pipes poru les prochaine commande
			dup2(g_list->pfd[i - 1][0], 0);
		if (i != g_list->nb_pipe) // pour dup la derniere commande avec notre sortie standar
			dup2(g_list->pfd[i][1], 1);
		while (g_list->nb_pipe != 0 && ++k < g_list->nb_pipe)
		{
			close(g_list->pfd[k][0]);
			close(g_list->pfd[k][1]);
		}
		exec_cmd(tmp, env);
	}
// 	free_str(tmp->pipex->split_path);
// 	free(tmp->pipex->exec_path);
// 	free(tmp->pipex);
 }

void	start_minishell(t_init ishell, char **env)
{
	t_lst_cmd	*mshell;
	t_lst_cmd	*tmp;
	int i;
	int k;
	int l;
	
	k = -1;
	i = -1;
	mshell = NULL;
	mshell = init_shell(ishell.new_line, mshell);
	tmp = mshell;
	while (tmp)
	{
 		if (ft_is_built_in(mshell->split_byspace[0]) == 1)
			exec_built_in(mshell, env);
		else
			cmd(tmp, env, ++i);
		tmp = tmp->next;
	}
	printf("i == %d\n", i);
	i = -1;
	tmp  = mshell;
	printf("nb pipe2 %d\n", g_list->nb_pipe);
	while (g_list->nb_pipe != 0 &&  ++i < g_list->nb_pipe)
	{
		close(g_list->pfd[i][0]);
		close(g_list->pfd[i][1]);
	}
	// while (tmp)
	// {

	// 	waitpid(mshell->pipex->child, NULL, 0);
	// 	tmp = tmp->next;
	// }
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
				g_list->nb_pipe = count_pipe(ishell.new_line);
				printf("nb pipe %d\n", g_list->nb_pipe);
				if (g_list->nb_pipe != 0)
				{
					printf("bucle fds\n");
					g_list->pfd = malloc(sizeof(int **) * g_list->nb_pipe);
					while(i < g_list->nb_pipe)
						g_list->pfd[i++] = malloc(sizeof(int) * 2);
					i = -1;
					while (++i < g_list->nb_pipe)
						pipe(g_list->pfd[i]);
				}
				start_minishell(ishell, env);
			}
		}
	}
}
