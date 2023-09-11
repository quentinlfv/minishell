/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasamadi <nasamadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:56:45 by nasamadi          #+#    #+#             */
/*   Updated: 2023/06/29 15:27:42 by nasamadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int	add_env(char *const *new_env, int i)
{
	char	*env_with_null;

	if (error_handle(new_env[i]) == 0)
	{
		if (ft_strchr(new_env[i], '=') == NULL)
		{
			env_with_null = ft_strjoin(new_env[i], "=");
			ft_lstadd_back(g_sh.env,
				ft_lstnew((void *)ft_strdup(env_with_null)));
			free(env_with_null);
		}
		else
		{
			ft_lstadd_back(g_sh.env,
				ft_lstnew((void *)ft_strdup(new_env[i])));
		}
		return (0);
	}
	else
		return (1);
}

static void	handle_aux_null(t_env *env)
{
	if (env->new_env[env->i][get_var_len(env->new_env[env->i])] != '=')
	{
		env->aux2 = ft_strjoin(env->new_env[env->i], "=");
		free(env->new_env[env->i]);
		env->new_env[env->i] = env->aux2;
	}
}

static int	process_var(t_env *env, char **tmp, char **aux)
{
	*tmp = ft_substr(env->new_env[env->i],
			0, get_var_len(env->new_env[env->i]));
	*aux = ft_getenv(*tmp);
	if (!*aux)
	{
		handle_aux_null(env);
		if (add_env(env->new_env, env->i))
		{
			free(*tmp);
			return (1);
		}
		free(*tmp);
	}
	else
	{
		free(*aux);
		update_var(*tmp, env->new_env[env->i]);
	}
	return (0);
}

int	export_var(char **new_env, char *tmp, char *aux, char *aux2)
{
	int		i;
	t_env	env;

	i = 0;
	env.new_env = new_env;
	env.aux2 = aux2;
	while (new_env[++i])
	{
		env.i = i;
		if (process_var(&env, &tmp, &aux) == 1)
			return (1);
	}
	return (0);
}
