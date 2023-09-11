/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasamadi <nasamadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:54 by nasamadi          #+#    #+#             */
/*   Updated: 2023/06/26 15:35:54 by nasamadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

/* Vérifie si un caractère est un caractère de fin de ligne */
int	is_term(int type, char **buff)
{
	if (g_sh.tok == NULL)
		return (0);
	if (g_sh.tok->type == type)
	{
		if (buff != NULL)
		{
			*buff = (char *)malloc(
					(ft_strlen(g_sh.tok->data) + 1) * sizeof(char));
			if (*buff == NULL)
				perror_ret("malloc", 0);
			ft_strcpy(*buff, g_sh.tok->data);
		}
		g_sh.tok = g_sh.tok->next;
		return (1);
	}
	g_sh.tok = g_sh.tok->next;
	return (0);
}
