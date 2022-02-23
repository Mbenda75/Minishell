/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 08:07:53 by adaloui           #+#    #+#             */
/*   Updated: 2022/02/23 19:00:36 by benmoham         ###   ########.fr       */
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

int count_pipe(char *str)
{
	int i;
	int pipe;

	i = 0;
	pipe = 0;
	while(str[i])
	{
		if (str[i] == '|')
			pipe++;
		i++;
	}
	return (pipe);
}
void  *free_lst(t_lst_cmd *lst)
{
    t_lst_cmd *tmp;
	
	free_str(lst->split_byspace);
    while (lst)
   {
		tmp = lst;
        lst = lst->next;
        free(tmp);
    }
    return (lst);
}

t_lst_cmd	*file_lst(char *split_bypipe)
{
	t_lst_cmd *lst;
	
	lst = malloc(sizeof(t_lst_cmd));
	lst->split_byspace = ft_split(split_bypipe, ' ');
	lst->next= NULL;
	for (int i = 0; lst->split_byspace[i];i++)
	printf("split by pipe== %s\n", lst->split_byspace[i]);
	return (lst);
}

t_lst_cmd	*create_lst(char *str, t_lst_cmd *lst, int nb_pipe)
{
	int i;
	char **split_bypipe;
	t_lst_cmd *tmp;
	
	tmp = NULL;
	i = 0;
	split_bypipe = ft_split(str, '|');
	while (i <= nb_pipe)
	{
		if (!lst)
		{
			lst = file_lst(split_bypipe[i]);
			tmp = lst;
		}
		else
		{
			tmp->next = file_lst(split_bypipe[i]);
			tmp = tmp->next;
		}
		i++;
	}
	return (lst);
}

int	main(int argc, char **argv, char **env)
{
	char	*buffer;
	int		nb_pipe;
	t_lst_cmd *lst;

	lst = NULL;
	//ft_signals();
	while (1)
	{
		buffer = readline("\033[0;33mSHELL DE MERDE\033[0;35m-> \033[0;37m");
		add_history(buffer);
		if (count_pipe(buffer) != 0)
		{
			nb_pipe = count_pipe(buffer);
		  	lst = create_lst(buffer, lst, nb_pipe);
		}
   		if (strcmp(buffer, "exit") == 0)
		{
			free(buffer);
			if (lst)
			{
				free_str(lst->split_byspace);
				free_lst(lst);	
			}
			return (0);
		}  
	}
	return (0);
}
 
 
/* 
 		while (split_bypipe[j]) 
		{
			split_byspace = ft_split(split_bypipe[j], ' ');
			printf("split == %s\n", split_byspace[0]);
			while(split_byspace[i])
			{
				printf("space == %s\n", split_byspace[i]);
				i++;
			}
			i =0;
			j++;
		} */