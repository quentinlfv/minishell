/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasamadi <nasamadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:52:53 by nasamadi          #+#    #+#             */
/*   Updated: 2023/06/26 15:33:36 by nasamadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

/* Récupérer le type du noeud, sans considérer la valeur AST_DATA */
int	ast_gettype(t_ast *ast)
{
	return (ast->type & (~AST_DATA));
}

/* Supprimer l'arbre en libérant les noeuds et les données */
void	ast_del(t_ast *ast)
{
	if (ast == NULL)
		return ;
	if (ast->type & AST_DATA)
		free(ast->data);
	ast_del(ast->left);
	ast_del(ast->right);
	free(ast);
}

/* Attacher des noeuds enfants à un noeud parent */
void	ast_attach(t_ast *root, t_ast *left, t_ast *right)
{
	if (root == NULL)
		return ;
	root->left = left;
	root->right = right;
}

/* Définir le type de noeud */
void	ast_settype(t_ast *ast, t_asttype type)
{
	if (ast == NULL)
		return ;
	ast->type = type;
}

/* Définir les données du noeud */
void	ast_setdata(t_ast *ast, char *data)
{
	if (ast == NULL || data == NULL)
		return ;
	ast->data = data;
	ast->type |= AST_DATA;
}
