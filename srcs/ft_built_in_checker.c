/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in_checker.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:03:44 by user42            #+#    #+#             */
/*   Updated: 2022/03/28 18:10:17 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_is_built_in(char *cmd)
{
	const char	*built_in[] = {"pwd", "cd", "exit",
		"env", "export", "echo", "unset", NULL};
	int			i;

	i = 0;
	if (cmd == NULL)
		return (FAILURE);
	while (built_in[i])
	{
		if (!strcmp(built_in[i], cmd))
			return (SUCCESS);
		i++;
	}
	return (FAILURE);
}

int	exec_built_in(t_lst_cmd *mshell, char **env)
{
	if (!ft_strcmp(mshell->split_byspace[0], "pwd"))
		ft_builtin_pwd(mshell->split_byspace);
	else if (!ft_strcmp(mshell->split_byspace[0], "cd"))  // Non 
		ft_built_in_cd(mshell->split_byspace, env);
	else if (!ft_strcmp(mshell->split_byspace[0], "exit")) // Non
		ft_built_in_exit(mshell);
	else if (!ft_strcmp(mshell->split_byspace[0], "echo"))
		ft_built_echo(mshell->split_byspace);
	else if (!ft_strcmp(mshell->split_byspace[0], "env"))
		ft_built_in_env(mshell->split_byspace);
	else if (!ft_strcmp(mshell->split_byspace[0], "export")) // Non
		ft_built_in_export(mshell->split_byspace);
	else if (!ft_strcmp(mshell->split_byspace[0], "unset")) // Non
		ft_built_in_unset(mshell->split_byspace);
	return (FAILURE);
}
