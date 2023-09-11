/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasamadi <nasamadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:56:13 by nasamadi          #+#    #+#             */
/*   Updated: 2023/06/29 15:13:58 by nasamadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	update_env(t_list **env)
{
	char	*n_path;

	n_path = malloc(sizeof(char) * (PATH_MAX + 1));
	if (!n_path)
		return ;
	if (getcwd(n_path, PATH_MAX) == NULL)
	{
		free(n_path);
		n_path = ft_getenv("PWD");
		if (!n_path)
			return ;
	}
	free((*env)->data);
	(*env)->data = ft_strjoin("PWD=", n_path);
	free(n_path);
}

int	goto_home(void)
{
	char	*home;
	t_list	*head;

	home = ft_getenv("HOME");
	head = *g_sh.env;
	if (!home || chdir(home) == -1)
	{
		print_error(home);
		free(home);
		return (1);
	}
	locate_env(head);
	free(home);
	return (0);
}

int	print_error(const char *dir)
{
	if (dir)
	{
		write(STDERR_FILENO, "cd: ", 4);
		write(STDERR_FILENO, dir, ft_strlen(dir));
		write(STDERR_FILENO, ": No such file or directory\n", 28);
	}
	else
		write(STDERR_FILENO, "cd: HOME not set\n", 17);
	return (1);
}

int	home_handler(void)
{
	if (goto_home() == 1)
		return (1);
	return (0);
}

void	set_env(t_list *env)
{
	locate_env(env);
}
