/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:28:06 by user42            #+#    #+#             */
/*   Updated: 2022/03/04 17:00:00 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_built_in_cd(char **path, char **envp)
{
    char **home;
    char   *tmp;

    if (path[1] == NULL)
    {
        
        home = ft_get_var_env(envp, "HOME");
        tmp = home[0];
        if (chdir(tmp) == -1)
		    perror("chdir()");
		free_str(home);
    }
    else if (path[2])
	{
		ft_custom_error("cd: too many arguments");
        return(FAILURE);
	}
	if (path[1] != NULL && chdir(path[1]) == -1)
		perror("chdir()");
    return (SUCCESS);
}