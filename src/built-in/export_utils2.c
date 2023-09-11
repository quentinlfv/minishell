/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasamadi <nasamadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 10:29:29 by nasamadi          #+#    #+#             */
/*   Updated: 2023/06/29 16:39:00 by nasamadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void	print_err(const char *new_env)
{
	write(STDERR_FILENO, "export: ", 8);
	write(STDERR_FILENO, new_env, ft_strlen(new_env));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, "not a valid identifier\n", 23);
}

static int	check_valid_var(char *new_env)
{
	int	i;

	i = 0;
	while (new_env[++i] != '\0' && new_env[i] != '=')
	{
		if (ft_isalnum(new_env[i]) == 0 && new_env[i] != '_')
		{
			print_err(new_env);
			return (1);
		}
	}
	if (new_env[i - 1] == '-')
	{
		print_err(new_env);
		return (1);
	}
	return (0);
}

int	error_handle(char *new_env)
{
	if (new_env[0] >= '0' && new_env[0] <= '9')
	{
		print_err(new_env);
		return (1);
	}
	if ((new_env[0] >= 'A' && new_env[0] <= 'Z')
		|| (new_env[0] >= 'a' && new_env[0] <= 'z')
		|| new_env[0] == '_')
	{
		if (check_valid_var(new_env) == 1)
			return (1);
		return (0);
	}
	else
	{
		print_err(new_env);
		return (1);
	}
}
