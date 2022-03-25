/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 15:23:39 by benmoham          #+#    #+#             */
/*   Updated: 2022/03/25 17:04:42 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void	close_wait(t_init ishell, t_lst_cmd *mshell)
{
	int i;
	t_lst_cmd *tmp;
	
	i = -1;
	tmp  = mshell;
 	while (tmp)
	{
		i = -1;
		while (g_list->nb_pipe != 0 &&  ++i < g_list->nb_pipe)
		{
			close(g_list->pfd[i][0]);
			close(g_list->pfd[i][1]);
		}
	 	waitpid(tmp->pipex->child, NULL, 0);
		tmp = tmp->next;
	}
	free_lst(mshell);
	free(ishell.new_line);
	free_str(ishell.cmd);
	free(ishell.prompt_line);
}

void	dup_exec(int i)
{
	int k;
	k = -1;

	if (i != 0) //pour dup notre entre standart dans les pipes pour les prochaine commande
	{
		dup2(g_list->pfd[i - 1][0], STDIN_FILENO);// dup2(pfd[0][0]) dans le canal de lecture du pipe dans stdin
		close(g_list->pfd[i - 1][0]);
	}
	if (i != g_list->nb_pipe) // pour dup la derniere commande avec notre sortie standar
	{
		dup2(g_list->pfd[i][1], STDOUT_FILENO); // dup2(pfd[0][1], 1) canal decriture du pipe dans stdout
		close(g_list->pfd[i][1]);
	}
  	while (g_list->nb_pipe != 0 && ++k < g_list->nb_pipe)
	{
		close(g_list->pfd[k][0]);
		close(g_list->pfd[k][1]);
	}
}


void	exec_cmd(t_lst_cmd *mshell, char **env)
{
	if (mshell->pipex->exec_path == NULL)
	{
		printf("exit exec\n");
		exit(1);
	}
	if (access(mshell->pipex->exec_path, F_OK) == 0)
		execve(mshell->pipex->exec_path, mshell->split_byspace, env);
}

void	cmd_fork(t_lst_cmd *tmp, char **env, int i)
{
	tmp->pipex->child = fork();
	
	if (tmp->pipex->child == -1)
	{
		write(2, "fork failed\n", 13);
		exit (1);
	}
	if (tmp->pipex->child == 0)
	{
		ft_signals();
		dup_exec(i);
		exec_cmd(tmp, env);
	}
}