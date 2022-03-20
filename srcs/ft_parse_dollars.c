/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_dollars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:08:49 by adaloui           #+#    #+#             */
/*   Updated: 2022/03/20 22:02:52 by adaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


/* Le but de cette fonction est de verifier si la variable d'environnement existee. Pour cela, on check
le non de la variable en lui retirant son '$' et en lui ajoutant un '=' pour le faire boucler dans un ft_strcmp*/

int ft_checK_env_var_existence(char *complete_var)
{
    t_env *verify;
    char *tmp_trim_dollar;
    char *tmp_add_equal;

    verify = g_list;
    tmp_add_equal = ft_strjoin(complete_var, "=");
    while (verify)
    {
        if (ft_strncmp(verify->content, tmp_add_equal, ft_strlen(tmp_add_equal)) == SUCCESS)
            return (SUCCESS);
        verify = verify->next;
    }
    //free(complete_var);
    return (FAILURE);
}

char *ft_change_dollar_var(char *word)
{
    t_env *verify;
    char *tmp_add_equal;

    verify = g_list;
    tmp_add_equal = ft_strjoin(word, "=");
    while (verify)
    {
        if (ft_strncmp(verify->content, tmp_add_equal, ft_strlen(tmp_add_equal)) == SUCCESS)
        {
            word = ft_substr(verify->content, ft_find_where_is_equal(verify->content) + 1, ft_strlen(verify->content));
            return (word);
        } 
        verify = verify->next; 
    }
    return (word);
}
/* Sers a join toutes les var dans une seule string*/
char *ft_modify_newline_content(char **receive_value)
{
    int i;
    char *temp;
    char *str;
    i = 0;
     
    if (receive_value[i + 1])
    {
        temp = "";
        while (receive_value[i])
        {
            str = receive_value[i];
            temp = ft_strjoin(temp, str);
            i++;
        }
       return (temp);
    }
    else if (receive_value[i + 1] == NULL) 
        str = receive_value[0];
    return (str);
}

int	count_dollar(char *str)
{
	int	i;
	int	dollar;

	i = 0;
	dollar = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != '$')
			dollar++;
		i++;
	}
	return (dollar);
}
char *ft_transform_dollar(char *str)
{
    int i;
    int j;
    char *word;
    char **split_byspace;
    char **split_bydollar;
    char **receive_value;
    int k;

    i = -1;
    j = 0;
    int dollar = count_dollar(str);
    split_byspace = ft_split(str, ' ');
    receive_value = malloc(sizeof(char *) * count_dollar(str) + 1);
    while (split_byspace[++i])
    {
        word = split_byspace[i];
        k = 0;
        if (ft_find_dollars(word) == SUCCESS)
        {
            split_bydollar = ft_split(word, '$');
            while (split_bydollar[k])
            {
                if (ft_checK_env_var_existence(split_bydollar[k]) == SUCCESS)
                {
                    printf("ICI WORD %s\n", word);
                    word = ft_change_dollar_var(split_bydollar[k]);
                    receive_value[j] = word;
                    j++;
                }
                else
                {
                    printf("LA WORD %s\n", word);
                    receive_value[j] = "";
                    j++;
                }
                k++;
            }
            receive_value[j] = '\0';
        }
        else
        {
            receive_value[j] = word;
            receive_value[j] = ft_strjoin(receive_value[j], " ");
            j++;
        }
    }
    return (ft_modify_newline_content(receive_value));

}

char *ft_transform_dollar_2(char *str)
{
    int i; // simple index pour slit_by_space
    int j; // va servir a connaitre la position de j
    char *word; // va servir de char* a envoyer dans le check env et le add env
    char **split_byspace; // split str par espace pour avoir toutes les strings
    char **split_bydollar;
    char **receive_value;
    int k;

    i = -1; // -1 pour la norme
    j = 0;
    int dollar = count_dollar(str);
    //printf("dollar = %d\n", dollar);
    split_byspace = ft_split(str, ' '); // je split par espace
    receive_value = malloc(sizeof(char *) * count_dollar(str) + 1);
    while (split_byspace[++i]) // je fais boucler mon split
    {
        word = split_byspace[i];
        k = 0;
        if (ft_find_dollars(word) == SUCCESS)
        {
            split_bydollar = ft_split(word, '$');
            while (split_bydollar[k])
            {
                if (ft_checK_env_var_existence(split_bydollar[k]) == SUCCESS)
                {
                    word = ft_change_dollar_var(split_bydollar[k]);
                    receive_value[j] = word;
                    j++;
                }
                else 
                {
                    printf("WORd = %s\n", split_bydollar[k]);
                    receive_value[j] = "";
                    printf("receive_value %s\n", receive_value[j]);
                    j++;
                }
                k++;
            }
            receive_value[j] = '\0';
        }
        else
        {
            receive_value[j] = word;
            receive_value[j] = ft_strjoin(receive_value[j], " ");
            j++;
        }
    }
    j = 0;
    while (receive_value[j])
    {
        printf("RECEIVE_VALUE = %s\n", receive_value[j]);
        j++;
    }
    return (ft_modify_newline_content(receive_value)); 
}


/*char *ft_transform_dollar(char *str)
{
    int i;
    char *word;
    char **split_bydollar;
    char *str_2;
    
    i = -1;
    split_bydollar = ft_split(str, '$');
    while (split_bydollar[++i])
    {
        word = split_bydollar[i];
        printf("\033[0;33mWORD = %s\n\033[0;37m", word);
        if (ft_checK_env_var_existence(word) == SUCCESS)
        {
            word = ft_change_dollar_var(word);
            split_bydollar[i] = ft_strdup(word);
        }
        else //sinon, on lui laisse le contenu de word
        {
            printf("\033[0;31mLA VARIABLE  %s N'EXISTE PAS\n\033[0;37m", word);
            word = ft_change_dollar_var(word);
            split_bydollar[i] = ft_strdup(word);
            printf("split_bysapce %s\n", split_bydollar[i]);
        }
    }
    return (ft_modify_newline_content(str, split_bydollar));
}*/