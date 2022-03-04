/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 22:59:07 by user42            #+#    #+#             */
/*   Updated: 2022/03/04 15:30:48 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_reinitialize_k()
{
	static int k;

	printf("k unset avant = %d\n", k);
	if (k > 0)
		k++;
	if (k == 0)		
		k++;
	g_list->unset_minus = k;
	//if (g_list->unset_minus == 0)
		k = 0;
	printf("k unset après = %d\n", k);
	printf("unset_minus UNSET = %d\n", g_list->unset_minus);
}

void	ft_built_in_unset_2(char **cmd, char **envp, t_decompte p)
{
	while (cmd[++p.j])
	{
        while (envp[++p.i])
        {
            if (ft_strnstr(envp[p.i], cmd[p.j], ft_strlen(cmd[p.j])))
            {
				ft_reinitialize_k(g_list->unset_minus);
				if (envp[p.i][ft_strlen(cmd[p.j])] == '=')
				{
               		envp[p.i] = memset(envp[p.i], 0, ft_strlen(envp[p.i]));
                	while (envp[p.i])
                	{
                    	envp[p.i] = envp[p.i + 1];
                    	p.i++;
                	}
                	p.i = 0;
                	break ;
				}
            }
		}
		p.i = 0;
    }
}

int	ft_check_variable(char **cmd)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			if (!((cmd[i][j] >= 'a' && cmd[i][j] <= 'z' )
				|| (cmd[i][j] >= 'A' && cmd[i][j] <= 'Z')
				|| (cmd[i][j] >= '0' && cmd[i][j] <= '9')
				|| (cmd[i][j] == '_')))
			return (ft_custom_error("unset: not valid identifier"));
			j++;
		}
		i++;
	}
	return (0);
}	

int ft_built_in_unset(char **cmd)
{
	t_decompte p;
	g_list->unset_minus = 0;
	int i;
    
    p.i = -1;
	p.j = 0;		
    if (cmd[1] == NULL)
        ft_putstr_fd("", 0);
    else
	{
	/*	if (k == 0)
			k = g_list->unset_minus;
		printf("k unset avant = %d\n", k);
		if (k > 0)
			k++;
		if (k == 0)
			k++;
		g_list->unset_minus = k;
		//if (g_list->unset_minus == 0)
			k = 0;*/
		i = ft_check_variable(cmd);
		if (i == 1)
			return (FAILURE);
		ft_built_in_unset_2(cmd, g_list->env_2, p);
		/*printf("k unset après = %d\n", k);
		printf("unset_minus UNSET = %d\n", g_list->unset_minus);*/

	}
    return (SUCCESS);
}
