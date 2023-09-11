/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasamadi <nasamadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:43 by nasamadi          #+#    #+#             */
/*   Updated: 2023/06/15 14:31:16 by nasamadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

/* test all redirections in order */
t_ast	*redir(void)
{
	t_tok	*save;
	t_ast	*new_node;

	save = g_sh.tok;
	g_sh.tok = save;
	new_node = redir_1();
	if (new_node != NULL)
		return (new_node);
	g_sh.tok = save;
	new_node = redir_2();
	if (new_node != NULL)
		return (new_node);
	return (NULL);
}

/* <redir in> */
t_ast	*redir_1(void)
{
	t_ast	*res;

	res = redir_in();
	if (res == NULL)
		return (NULL);
	ast_attach(res, NULL, NULL);
	return (res);
}

/* <redir out> */
t_ast	*redir_2(void)
{
	t_ast	*res;

	res = redir_out();
	if (res == NULL)
		return (NULL);
	ast_attach(res, NULL, NULL);
	return (res);
}
