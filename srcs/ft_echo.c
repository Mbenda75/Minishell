/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 22:05:30 by user42            #+#    #+#             */
/*   Updated: 2022/03/03 19:26:48 by adaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void ft_built_in_echo_n(char ***args, int *newline)
{
	char	**ptr;
	char	*s;

	ptr = *args;
	while (1)
	{
		if (*ptr && **ptr == '-' && *(*ptr + 1) == 'n')
		{
			s = *ptr;
			s++;
			while (*s == 'n')
				s++;
			if (!*s)
			{
				*newline = 0;
				ptr++;
				continue ;
			}
		}
		break ;
	}
	*args = ptr;
}

int ft_built_in_echo(char **cmd)
{
    int		newline;
	char	**ptr;

	ptr = cmd + 1;
	newline = 1;
	ft_built_in_echo_n(&ptr, &newline);
	while (1)
	{
		if (!*ptr)
			break ;
		if (printf("%s", *ptr++) < 0)
			return (ft_system_error());
		if (*ptr && printf(" ") < 0)
			return (ft_system_error());
	}
	if (!newline)
		return (SUCCESS);
	if (printf("\n") < 0)
		return (ft_system_error());
	return (SUCCESS);
}

/*int	built_in_echo(char **cmd)
{
    int i;
	int j = 0;

	i = 1;
	if (!cmd)
		ft_putstr_fd("\n", 0);
	while (cmd[i])
    {
		ft_putstr_fd(cmd[i], 0);
		if (cmd[i] != "\0")
			ft_putstr_fd(" ", 0);
		i++;
	}
	ft_putstr_fd("\n", 0);
	return (0);
}

int ft_built_in_echo(char **cmd)
{
    int i;
	int j;
	char *var_env = NULL;

	i = 0;
	if (cmd[1] == NULL)
	{	
		ft_putstr_fd("\n", 0);
		return (0);
	}
	if (strcmp(cmd[1], "-n") == 0)
	{
		i = 2;
		while (cmd[i])
		{
			ft_putstr_fd(cmd[i], 0);
			i++;
		}
		return (0);
	}
	if (cmd[1][0] == '$' && cmd[1][1] == '?')
		printf("%d\n", g_list->exit_value);
    else
        built_in_echo(cmd);
    ft_free_charr(cmd);
    return (0);
}*/