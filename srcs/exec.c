/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 15:23:39 by benmoham          #+#    #+#             */
/*   Updated: 2022/03/21 20:15:38 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/* 
int *init_pipe(int count)
{
	int *fd;
	int i;
	
	fd = malloc(sizeof(int) * count);
	i = 1;
	while (i < count  + 1)
	{
		
		pipe(fd[i * 2]);
		i++;
	}
	return (fd);	
} */

t_pipex *init_pipex(char **split_byspace, char *str)
{
	t_pipex	*pipex;
	int i;

	i = 0;
	pipex = NULL;
	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
		return(NULL);
	pipex->line_path = search_path(g_list);
	//pipex->pfd = init_pipe(count_pipe(ishell->new_line);
	pipex->split_path = ft_split(pipex->line_path, ':');
	pipex->exec_path = boucle_path(pipex->split_path, split_byspace);
	pipex->nb_pipe = count_pipe(str);
	return (pipex);
}


void	exec_cmd(t_lst_cmd *mshell, char **env)
{
	if (mshell->pipex->exec_path == NULL)
	{
		printf("exit exec\n");
		// free_str(mshell->pipex->split_path);
		// free(mshell->pipex->exec_path);
		// free(mshell->pipex);
		return ;
	}
	if (access(mshell->pipex->exec_path, F_OK) == 0)
		execve(mshell->pipex->exec_path, mshell->split_byspace, env);
}
