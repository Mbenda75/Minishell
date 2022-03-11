/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 15:23:39 by benmoham          #+#    #+#             */
/*   Updated: 2022/03/11 19:01:34 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int start_exec(t_pipex *pipex, t_lst_cmd *mshell, char **env)
{
	pipex->line_path = search_path(g_list);
	pipex->split_path = ft_split(pipex->line_path, ':');
	pipex->exec_path = boucle_path(pipex->split_path, mshell->split_byspace);
	printf("split_path == %s\n", pipex->exec_path);
	if (pipex->exec_path == NULL)
	{
		printf("exit exec\n");
		free_str(pipex->split_path);
		free(pipex->exec_path);	
		return (1);
	}
	pipex->child = fork();
	if (pipex->child == -1)
	{
		write(2, "fork failed\n", 13);
		exit (1);
	}
	if (pipex->child == 0)
	{
		if (access(pipex->exec_path, F_OK) == 0)
				execve(pipex->exec_path, mshell->split_byspace, env);
	}
	waitpid(pipex->child, NULL, 0);
	free_str(pipex->split_path);
	free(pipex->exec_path);	
	return (0);
}