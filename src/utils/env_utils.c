/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasamadi <nasamadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:52:05 by nasamadi          #+#    #+#             */
/*   Updated: 2023/06/15 14:31:16 by nasamadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	**get_env_char(void)
{
	char	**env;
	t_list	**aux;
	int		i;

	i = 0;
	env = (char **)malloc(sizeof(char *) * (ft_lstsize(*g_sh.env) + 1));
	aux = g_sh.env;
	while (*aux)
	{
		env[i++] = ft_strdup((char *)(*aux)->data);
		aux = &(*aux)->next;
	}
	env[i] = NULL;
	return (env);
}
