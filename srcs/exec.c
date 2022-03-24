/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 15:23:39 by benmoham          #+#    #+#             */
/*   Updated: 2022/03/24 23:17:23 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int	close_wait(t_init ishell, t_lst_cmd *mshell)
{
	int i;
	pid_t j;
	int status;
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
		printf("NE ME TOUCHEZ PAS 1\n");
	 	j = waitpid(tmp->pipex->child, &status, 0);
		printf("NE ME TOUCHEZ PAS 1\n");
		tmp = tmp->next;
		printf("NE ME TOUCHEZ PAS 2\n");

	}
	free_lst(mshell);
	free(ishell.new_line);
	free_str(ishell.cmd);
	free(ishell.prompt_line);
	printf("NE ME TOUCHEZ PAS popololo\n");
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	return (status);
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
	int j;

	j = 0;
	
	if (mshell->pipex->exec_path == NULL)
	{
		printf("exit exec\n");
		return ;
	}
	while (mshell->split_byspace[j])
	{
		printf("JE SUIS LA = %s\n", mshell->split_byspace[j]);
		j++;
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
		dup_exec(i);
		exec_cmd(tmp, env);
		
	}
}