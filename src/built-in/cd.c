/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasamadi <nasamadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:56:23 by nasamadi          #+#    #+#             */
/*   Updated: 2023/06/29 15:13:18 by nasamadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	goto_dir(const char *dir)
{
	char	*aux;
	char	*tmp;
	char	*home;

	aux = ft_substr(dir, 1, ft_strlen(dir) - 1);
	home = ft_getenv("HOME");
	if (!home)
	{
		free(aux);
		return (1);
	}
	aux = ft_realloc(aux, ft_strlen(dir) + ft_strlen(home) + 1);
	tmp = ft_strjoin(home, aux);
	if (chdir(tmp) == -1)
	{
		print_error(tmp);
		free(home);
		free(aux);
		free(tmp);
		return (1);
	}
	free(home);
	free(aux);
	free(tmp);
	return (0);
}

static int	goto_oldpwd(t_list *env)
{
	char	*opwd;
	char	*tmp;
	char	*pwd;

	tmp = NULL;
	pwd = NULL;
	opwd = ft_getenv("OLDPWD");
	if (!opwd)
	{
		write(STDERR_FILENO, "cd: OLDPWD not set\n", 19);
		return (1);
	}
	if (chdir(opwd) == -1)
	{
		write(STDERR_FILENO, "cd: ", 4);
		write(STDERR_FILENO, opwd, ft_strlen(opwd));
		write(STDERR_FILENO, ": No such file or directory\n", 28);
		free(opwd);
		return (1);
	}
	free(opwd);
	set_oldpwd(env, tmp, pwd);
	locate_env(env);
	return (0);
}

static int	process_dir_args(t_dir *d)
{
	if (!d->dir[1] || (!ft_strncmp(d->dir[1], "~\0", 2)
			|| !ft_strncmp(d->dir[1], "~/", 2)))
	{
		if (!d->dir[1] || !ft_strncmp(d->dir[1], "~\0", 2))
		{
			if (home_handler() == 1)
				return (1);
			return (0);
		}
		else if (goto_dir(d->dir[1]) == 1)
			return (1);
	}
	else if (d->dir[1][0] != '\0' && chdir(d->dir[1]) == -1)
		return (print_error(d->dir[1]));
	else if (d->dir[2])
	{
		write(STDERR_FILENO, "cd: too many arguments\n", 23);
		return (1);
	}
	else
		set_env(*g_sh.env);
	return (0);
}

int	ft_changedir(char **dir)
{
	t_dir	d;

	d.dir = dir;
	if (d.dir[1] && ft_strncmp(d.dir[1], "-", 1) == 0)
		return (goto_oldpwd(*g_sh.env));
	set_oldpwd(*g_sh.env, d.tmp, d.pwd);
	return (process_dir_args(&d));
}
