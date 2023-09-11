/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasamadi <nasamadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:52:58 by nasamadi          #+#    #+#             */
/*   Updated: 2023/06/26 15:35:31 by nasamadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	ast_insert(t_ast *root, t_ast *node, t_bool on_right)
{
	t_ast	*aux;

	if (root == NULL || node == NULL)
		return ;
	if (on_right)
	{
		aux = root->right;
		root->right = node;
		node->right = aux;
		node->left = NULL;
	}
	else
	{
		aux = root->left;
		root->left = node;
		node->left = aux;
		node->right = NULL;
	}
}

/* Insérer un noeud 'et' ou 'ou' en haut de l'arbre */
void	ast_insert_and_or(t_ast **root, t_ast *new_root, t_bool last)
{
	if (root == NULL || new_root == NULL)
		return ;
	if (*root == NULL)
		*root = new_root;
	else
	{
		if (last == FALSE)
		{
			(*root)->right = new_root->left;
			new_root->left = (*root);
			*root = new_root;
		}
		else
			(*root)->right = new_root;
	}
}
