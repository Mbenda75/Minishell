/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 08:07:53 by adaloui           #+#    #+#             */
/*   Updated: 2022/02/21 14:17:24 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    free_str(char **s)
{
        int     line;

        line = 0;
        while (s[line])
        {
                free(s[line]);
                line++;
        }
        free(s);
}

char **cpy_env(char **env)
{
	char **cpy_env;
	int i;

	i = 0;
	while (env[i])
		i++;
	if (!(cpy_env = (char **)malloc(sizeof(char *) * (i + 1))))
		return (0);
	i = 0;
	while (env[i])
	{
		cpy_env[i] = ft_strdup(env[i]);
		i++;
	}
	cpy_env[i] = 0;
	return (cpy_env);
}

void	print_env(char **env)
{
	int i;

	i = 0;
	while(env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}

int double_quot(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		
		if (str[i] == 34)
			return (1);
		i++;
	}
	return (0);
}
int simple_quot(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		
		if (str[i] == 39)
			return (1);
		i++;
	}
	return (0);
}
int	main(int argc, char **argv, char **env)
{
	char	*buffer;
	int		i;
	
	i = 0;
	ft_signals();
	while (1)
	{
		buffer = readline("\033[0;33madaloui\033[0;35m42-> \033[0;37m");
		add_history(buffer);
		if (strcmp(buffer, "exit") == 0)
		{
			free(buffer);
			return (0);
		}
	}
	return (0);
}
 