/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 15:23:39 by benmoham          #+#    #+#             */
/*   Updated: 2022/03/24 17:43:06 by adaloui          ###   ########.fr       */
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
		printf("premier\n");
		printf("i premier == %d\n", i);

		dup2(g_list->pfd[i - 1][0], 0); // dup2(pfd[0][0]) dans le canal de lecture du pipe dans stdin

	}
	if (i != g_list->nb_pipe) // pour dup la derniere commande avec notre sortie standar
	{
		printf("2eme\n");
		printf("i 2emme == %d\n", i);
		
		dup2(g_list->pfd[i][1], 1); // dup2(pfd[0][1], 1) canal decriture du pipe dans stdout
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
		return ;
	}
	printf("split_byspace == %s\n", mshell->split_byspace[1]);
	//printf("path == %s\n", mshell->pipex->exec_path);
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
		dup_exec(i);
		exec_cmd(tmp, env);
		
	}
}