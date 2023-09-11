/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasamadi <nasamadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:56:45 by nasamadi          #+#    #+#             */
/*   Updated: 2023/06/26 15:17:31 by nasamadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int	add_env(char *const *new_env, int i)
{
	if (error_handle(new_env[i]) == 0)
	{
		ft_lstadd_back(g_sh.env,
			ft_lstnew((void *)ft_strdup(new_env[i])));
		return (0);
	}
	else
		return (1);
}

int	export_var(char **new_env, char *tmp, char *aux, char *aux2)
{
	int	i;

	i = 0;
	while (new_env[++i])
	{
		tmp = ft_substr(new_env[i], 0, get_var_len(new_env[i]));
		aux = ft_getenv(tmp);
		if (!aux)
		{
			if (new_env[i][get_var_len(new_env[i])] != '=')
			{
				aux2 = ft_strjoin(new_env[i], "=");
				free(new_env[i]);
				new_env[i] = aux2;
			}
			if (add_env(new_env, i))
			{
				free(tmp);
				return (1);
			}
			free(tmp);
		}
		else
		{
			free(aux);
			update_var(tmp, new_env[i]);
		}
	}
	return (0);
}

void	free_aux(char *tmp, char *aux)
{
	free(tmp);
	free(aux);
}

static void	print_err(const char *new_env)
{
	write(STDERR_FILENO, "export: ", 8);
	write(STDERR_FILENO, new_env, ft_strlen(new_env));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, "not a valid identifier\n", 23);
}

int	error_handle(char *new_env)
{
	int	i;

	i = 0;
	if (new_env[0] >= '0' && new_env[0] <= '9')
	{
		print_err(new_env);
		return (1);
	}
	if ((new_env[0] >= 'A' && new_env[0] <= 'Z')
		|| (new_env[0] >= 'a' && new_env[0] <= 'z')
		|| new_env[0] == '_')
	{
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
	else
	{
		print_err(new_env);
		return (1);
	}
}
