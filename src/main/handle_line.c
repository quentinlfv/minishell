/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasamadi <nasamadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:54:08 by nasamadi          #+#    #+#             */
/*   Updated: 2023/06/29 15:01:59 by nasamadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

/************************* TEST FUNC. *************************/

/* print binary tree in 2d */
/*static void print_ast(t_ast *root, int space)
{
	// spaces between levels
	#define COUNT 10

	int		nd;
	char	*type;

	if (root == NULL)
		return;

	// increase distance between levels
	space += COUNT;

	// process right child
	print_ast(root->right, space);

	// print current node
	printf("\n");
	for (int i = COUNT; i < space; i++)
		printf(" ");
	// get ast node type
	nd = ast_gettype(root);
	if (nd & AST_PIPE)
		type = ft_strdup("|");
	else if (nd & AST_SEQ)
		type = ft_strdup(";");
	else if (nd & AST_AND)
		type = ft_strdup("&&");
	else if (nd & AST_OR)
		type = ft_strdup("||");
	else if (nd & AST_REDIR)
		type = ft_strdup("redir");
	else if (nd & AST_RD_TRUNC)
		type = ft_strdup(">");
	else if (nd & AST_RD_APPEND)
		type = ft_strdup(">>");
	else if (nd & AST_RD_HDOC)
		type = ft_strdup("<<");
	else if (nd & AST_RD_INFILE)
		type = ft_strdup("<");
	else if (nd & AST_CMD)
		type = ft_strdup("cmd");
	else if (nd & AST_ARG)
		type = ft_strdup("arg");
	else
		type = ft_strdup("error: unknow type");

	// print type and data
	if (root->type & AST_DATA)
		printf("type: %s, data: %s\n", type, root->data);
	else
		printf("type: %s\n", type);
	free(type);

	// process left child
	print_ast(root->left, space);
}*/

/* print tokens */
/*static void print_tokens(t_lexer *lex)
{
	t_tok *tmp;

	printf("------------------------------------\n");
	printf("n_tok: %d\n", lex->n_toks);
	tmp = lex->tok_lst;
	while (tmp)
	{
		printf("type: %d, data: %s\n", tmp->type, tmp->data);
		tmp = tmp->next;
	}
	printf("------------------------------------\n");
}*/

/************************* TEST FUNC. *************************/

/* free lexer and ast */
static void	free_all(t_lexer *lex, t_ast *ast)
{
	if (lex != NULL)
		lexer_del(lex);
	if (ast != NULL)
		ast_del(ast);
}

/* check if line is valid */
static int	check_line(char *line, t_bool is_alloc)
{
	char	*aux;
	int		i;

	i = 0;
	while (ft_isblank(line[i]))
		i++;
	if (line == NULL || *line == '\0' || *line == '\n' || line[i] == '#')
	{
		if (is_alloc == TRUE)
			free(line);
		return (1);
	}
	aux = line;
	while (*aux != '\0')
	{
		if (ft_isblank(*aux) == 0)
			break ;
		aux++;
	}
	if (*aux == '\0' && is_alloc == TRUE)
		free(line);
	return (*aux == '\0');
}

/* handle lexer building and error processing */
static int	handle_lexer(char *line, t_lexer *lex)
{
	int	ret;

	ret = lexer_build(line, ft_strlen(line), lex);
	if (ret <= 0 && g_sh.tokdel == FALSE)
		write(STDERR_FILENO,
			"error: syntax error near unexpected token `newline'\n", 53);
	return (ret <= 0);
}

/* handle line -> lexer, parser and exec */
void		handle_line(char *line, t_bool is_alloc)
{
	t_lexer	lex;
	t_ast	*ast;

	ast = NULL;
	if (check_line(line, is_alloc))
		return ;
	if (handle_lexer(line, &lex))
	{
		if (is_alloc == TRUE)
			free(line);
		lexer_del(&lex);
		return ;
	}
	if (is_alloc == TRUE)
		free(line);
	if (lex.n_toks == 0 || parse(&lex, &ast))
	{
		free_all(&lex, ast);
		return ;
	}
	if (exec_heredoc(ast) == 0)
		exec_ast(ast);
	free_all(&lex, ast);
}
