/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaloui <adaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:09:23 by user42            #+#    #+#             */
/*   Updated: 2022/03/25 18:02:26 by adaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_skip_whitespaces(char *cmd)
{
	int i;

	i = 0;
	while (cmd[i] == ' ' || cmd[i] == '\t' || cmd[i] == '\n') //on évite les whitespace
		i++;
	return (i);
}

int ft_check_signs(char *cmd, int i, int sign)
{
	if (cmd[i] == '-') //si on tombe sur un - , on met la variable i à -1 et on incrémente
	{
		sign = -1;
		i++;
	}
	else if (cmd[i] == '+') //sinon si on tombe sur un + on met i à 1 et on incrémente. On utilise un else if car cela permet de gérer le cas du +-0 ou -+0 
	{
		sign = 1;
		i++;
	}
	else 
		sign = 1; //sinon on met i à 1 car même en l'absence de +, le exit value est positif
	return (sign);
}

int ft_calc_exit_nb(char *cmd, int *exit_value)
{
	int i; // simple index qui nous permet de naviguer dans cmd
	int sign; //sert simplement à déterminer le signe que sera exit value en vertue de la valeur de inscrite dans cmd
	unsigned long long int_lim; //sert à vérifier que la valeur envoyée par cmd ne soit pas > MAX_INT ou < MIN INT, d'où l'usage du type ulong long

	int_lim = 0; // on met int_lim à 0 car la formule 0 * 10 = 0 et après on ajoutera les chiffres les uns après les autres avec + cmd[i] - 48
	sign = 0;
	i = ft_skip_whitespaces(cmd); //nous fait skip les whitespaces et incrémente i; Cette fonction est présente pour cause de norme
	if (cmd[i] == '-' || cmd[i] == '+') //nous permet de savoir si, juste après d'éventuels whitespace il y'a un signe + ou - pour déterminer le signe
	{
		sign = ft_check_signs(cmd, i, sign); // nous permet de savoir s'il y'a un signe + ou - et nous permet d'éviter le cas de figure ++++ ou --- ou -+ ou +-
		i++; // on incrémente dans ce cas i de un pour tomber sur des chiffres (ex : cmd =-150) on passe du cmd[i]= - et cmd[i + 1] = 1
	}
	else // s'il n'y a pas de signe alors notre nombre est forcément posétif, donc on met sign = 1; 
		sign = 1; //sign est soit = à 1 soit = à -1; En multipliant signe par int_lim on obtient un nombre négatif ou positif à la fin de la fonction
	while(cmd[i] >= '0' && cmd[i] <= '9')//on a donc un index qui est suffisement incrémenté pour être arrivé aux chiffres, donc tant qu'on est sur des chiffres
	{
		int_lim = int_lim * 10 + (cmd[i] - 48); //la variable long va prendre un à un les chiffres de cmd
		if ((int_lim > __LONG_LONG_MAX__ && sign == 1) || (int_lim > __LONG_LONG_MAX__ && sign == -1)) //si ces derniers sont > MAX_INT ou < MAX_INT on renvoit une erreur --> exit ne traite pas ces cas là
			return (FAILURE);
		i++;
	}
	if (cmd[i] != '\0') //sinon, s'il y'a des lettres au début ou à la fin de l'argument, il rentrera dans ce if qui renverra une erreur;
		return (FAILURE);
	*exit_value = sign * int_lim; //si tout s'est bien passé, alors exit_value va prendre la valeur de lim_int * le signe (1 ou -1)
	return (SUCCESS); // on renvoit success et pas exit_value, c'est c'est &exit_value qu'on modifie
}

void	ft_free_lst_print_and_exit(t_lst_cmd *mshell, int exit_value)
{
	if(g_list->nb_pipe != 0)
		free_fd(g_list->pfd);
	free_env(g_list);
	free_lst(mshell); // on free tout avec tes fonctions
	exit(exit_value); // ont exit avec la valeur de exit value obtenue soit au travers des cas d'erreurs soit avec ft_calc_exit_nb	
}

int	ft_built_in_exit(t_lst_cmd *mshell)
{
	int	exit_value;

	if (mshell->split_byspace[1] == NULL) //cas où l'arg[1] est vide, l'exit value est de 0
		exit_value = 0;
	else if (mshell->split_byspace[2] != NULL) // lorsqu'il y'a plus de deux caractère, il y'a 2 sorties possible soit numeric arg required, soit too many arg (n'exit pas)
	{
		if (ft_calc_exit_nb(mshell->split_byspace[1], &exit_value) == FAILURE) // cas de figure où l'arg[1] est un caractère non-numérique
		{
			printf("exit\nminishell: exit: numeric argument required\n");
			exit_value = 2; // on renvoit 2 et pas 1 (simple code d'erreur) car c'est le code d'erreur pour cas où il n'y a pas de chiffres ou si les chiffres sont > MAX INT ou < MIN INT
		}
		else // cas de figure ou l'arg[1] est un caractère numérique dans ce cas là, la fonction exit n'exit pas, on retourne FAILURE alors
		{
			printf("exit\nminishell: exit: too many arguments\n");
			return (FAILURE); // on exit pas malgré le fait qu'il y'ait une erreur, on renvoit simplement failure
		}
	}
	else if (ft_calc_exit_nb(mshell->split_byspace[1], &exit_value) == FAILURE) //s'il y'a qu'un argument et que ce dernier n'est pas vide il faut checker son contenu
	{																			//si son contenu n'est pas bon, alors on renvoit 2
		printf("exit\nminishell: exit: numeric argument required\n");
		exit_value = 2; //on renvoit encore 2, car c'est la même erreur : cas où il n'y a pas de chiffres ou si les chiffres sont > MAX INT ou < MIN INT
	}
	else  //aucun des cas de figure précédant donc un simple exit suivant d'un nombre compris dans long long (limite debash avant de renvoyer numeric arg required bash)
		printf("exit\n");
	ft_free_lst_print_and_exit(mshell, exit_value); //sert simplement à free et à écrire exit --> mesure due à la norme
	return(SUCCESS);
}
