/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasamadi <nasamadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:56:40 by nasamadi          #+#    #+#             */
/*   Updated: 2023/06/27 14:45:00 by nasamadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include <errno.h>

static int	validate_exit_code(char *const *exitc, int i)
{
	if (exitc && exitc[0] && exitc[1] && exitc[2])
	{
		write(STDERR_FILENO, "exit: too many arguments\n", 25);
		return (1);
	}
	while (exitc[1] && exitc[1][i])
	{
		if (!ft_isdigit(exitc[1][i++]))
		{
			write(STDERR_FILENO, "exit: ", 6);
			write(STDERR_FILENO, exitc[1], ft_strlen(exitc[1]));
			write(STDERR_FILENO, ": numeric argument required\n", 28);
			g_sh.status = 2;
			ft_lstclear(g_sh.env, free);
			free(g_sh.env);
			exit(2);
		}
	}
	return (0);
}

static void	ft_exit_error(char **exitc)
{
	write(STDERR_FILENO, "exit: ", 6);
	write(STDERR_FILENO, exitc[1], ft_strlen(exitc[1]));
	write(STDERR_FILENO, ": numeric argument required\n", 28);
	ft_lstclear(g_sh.env, free);
	free(g_sh.env);
	exit(2);
}

static void	ft_process_exit_code(long exit_code)
{
	g_sh.status = (unsigned char)exit_code;
	ft_lstclear(g_sh.env, free);
	free(g_sh.env);
	exit((unsigned char)exit_code);
}

static void	ft_exit_no_arg(void)
{
	ft_lstclear(g_sh.env, free);
	free(g_sh.env);
	exit(g_sh.status);
}

int	ft_exit(char **exitc)
{
	long	exit_code;
	int		i;
	char	*endptr;

	i = 0;
	if (exitc[1] && (exitc[1][i] == '+' || exitc[1][i] == '-'))
		i++;
	if (validate_exit_code(exitc, i) == 1)
		return (1);
	if (exitc[1])
	{
		errno = 0;
		exit_code = strtol(exitc[1], &endptr, 10);
		if ((errno == ERANGE
				&& (exit_code == LONG_MAX || exit_code == LONG_MIN))
			|| (errno != 0 && exit_code == 0) || endptr == exitc[1])
			ft_exit_error(exitc);
		ft_process_exit_code(exit_code);
	}
	ft_exit_no_arg();
	return (0);
}

/*int	ft_exit(char **exitc)
{
	long	exit_code;
	int		i;
	char	*endptr;

	i = 0;
	if (exitc[1] && (exitc[1][i] == '+' || exitc[1][i] == '-'))
		i++;
	if (validate_exit_code(exitc, i) == 1)
		return (1);
	if (exitc[1])
	{
		errno = 0;
		exit_code = strtol(exitc[1], &endptr, 10);
		if ((errno == ERANGE && (exit_code == LONG_MAX
					|| exit_code == LONG_MIN))
			|| (errno != 0 && exit_code == 0))
		{
			write(STDERR_FILENO, "exit: ", 6);
			write(STDERR_FILENO, exitc[1], ft_strlen(exitc[1]));
			write(STDERR_FILENO, ": numeric argument required\n", 28);
			ft_lstclear(g_sh.env, free);
			free(g_sh.env);
			exit(2);
		}
		if (endptr == exitc[1])
		{
			write(STDERR_FILENO, "exit: ", 6);
			write(STDERR_FILENO, exitc[1], ft_strlen(exitc[1]));
			write(STDERR_FILENO, ": numeric argument required\n", 28);
			ft_lstclear(g_sh.env, free);
			free(g_sh.env);
			exit(2);
		}
		g_sh.status = (unsigned char)exit_code;
		ft_lstclear(g_sh.env, free);
		free(g_sh.env);
		exit((unsigned char)exit_code);
	}
	ft_lstclear(g_sh.env, free);
	free(g_sh.env);
	exit(g_sh.status);
	return (0);
}*/
