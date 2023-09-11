/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasamadi <nasamadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:52:25 by nasamadi          #+#    #+#             */
/*   Updated: 2023/06/29 15:09:19 by nasamadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include <sys/stat.h>

/* add built in to built in list */
static void	add_blti(t_blti **head, char *name, int (*f)(char **))
{
	t_blti	*new;
	t_blti	*aux;

	new = (t_blti *)malloc(sizeof(t_blti));
	if (new == NULL)
		perror_exit("malloc");
	new->name = name;
	new->f = f;
	new->next = NULL;
	if (*head != NULL)
	{
		aux = *head;
		while (aux->next)
			aux = aux->next;
		aux->next = new;
	}
	else
		*head = new;
}

/* initialise built ins */
static t_blti	*init_blti(void)
{
	t_blti	*bi;

	bi = NULL;
	add_blti(&bi, "echo", ft_echo);
	add_blti(&bi, "cd", ft_changedir);
	add_blti(&bi, "pwd", ft_get_wdir);
	add_blti(&bi, "export", ft_export);
	add_blti(&bi, "unset", ft_unset);
	add_blti(&bi, "env", ft_env);
	add_blti(&bi, "exit", ft_exit);
	return (bi);
}

/* initialise global var */
static void	initialise_vars(void)
{
	g_sh.status = EXIT_SUCCESS;
	g_sh.bi = init_blti();
	g_sh.is_child = FALSE;
	g_sh.is_expd = FALSE;
	g_sh.fd_bak[0] = dup(STDIN_FILENO);
	g_sh.fd_bak[1] = dup(STDOUT_FILENO);
}

/* initialise shell */
void	init_shell(void)
{
	extern char	**environ;

	fill_env(environ);
	initialise_vars();
	sig_parent();
	read_config();
}
