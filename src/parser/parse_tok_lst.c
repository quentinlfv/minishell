/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tok_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasamadi <nasamadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:53:49 by nasamadi          #+#    #+#             */
/*   Updated: 2023/06/15 14:31:16 by nasamadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

/* test token list */
t_ast	*tok_lst(void)
{
	t_tok	*save;
	t_ast	*new_node;

	save = g_sh.tok;
	g_sh.tok = save;
	new_node = tok_lst_1();
	if (new_node != NULL)
		return (new_node);
	g_sh.tok = save;
	new_node = tok_lst_2();
	if (new_node != NULL)
		return (new_node);
	g_sh.tok = save;
	new_node = tok_lst_3();
	if (new_node != NULL)
		return (new_node);
	g_sh.tok = save;
	new_node = tok_lst_4();
	if (new_node != NULL)
		return (new_node);
	return (NULL);
}

/* <name> <token list> */
t_ast	*tok_lst_1(void)
{
	char	*name;

	if (g_sh.cmd_ast->data == NULL)
	{
		if (!is_term(TOK, &name))
			return (NULL);
		ast_setdata(g_sh.cmd_ast, name);
		tok_lst();
		return (g_sh.cmd_ast);
	}
	return (NULL);
}

/* <redir> <token list> */
t_ast	*tok_lst_2(void)
{
	t_ast	*res;

	res = redir();
	if (res == NULL)
		return (NULL);
	tok_lst();
	ast_insert(g_sh.cmd_ast, res, FALSE);
	return (res);
}

/* <token> <token list> */
t_ast	*tok_lst_3(void)
{
	char	*arg;
	t_ast	*res;

	if (!is_term(TOK, &arg))
		return (NULL);
	res = (t_ast *)malloc(sizeof(t_ast));
	ast_settype(res, AST_ARG);
	ast_setdata(res, arg);
	tok_lst();
	ast_insert(g_sh.cmd_ast, res, TRUE);
	return (res);
}

/* (null) */
t_ast	*tok_lst_4(void)
{
	return (NULL);
}
