/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_len.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasamadi <nasamadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:52:00 by nasamadi          #+#    #+#             */
/*   Updated: 2023/06/29 15:09:51 by nasamadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int	get_var_len(const char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	return (i);
}

static void	handle_c_flag(char *argv[], int argc)
{
	if (argc < 3)
	{
		write(STDERR_FILENO, "-c: option requires an argument\n", 32);
		exit(2);
	}
	else
	{
		handle_line(argv[2], FALSE);
		exit(g_sh.status);
	}
}

static void	handle_dir_flag(struct stat s, char *arg)
{
	if (S_ISDIR(s.st_mode))
	{
		write(STDERR_FILENO, arg, ft_strlen(arg));
		write(STDERR_FILENO, ": Is a directory\n", 16);
		exit(126);
	}
	else
	{
		write(STDERR_FILENO, "error: no valid arguments\n", 26);
		exit(127);
	}
}

void	handle_flags(int argc, char *argv[])
{
	struct stat	s;

	if (argc > 1)
	{
		if (!ft_strncmp(argv[1], "-c\0", 3))
		{
			handle_c_flag(argv, argc);
		}
		else if (stat(argv[1], &s) == 0)
		{
			handle_dir_flag(s, argv[1]);
		}
		else
		{
			write(STDERR_FILENO, "error: no valid arguments\n", 26);
			exit(127);
		}
	}
}
