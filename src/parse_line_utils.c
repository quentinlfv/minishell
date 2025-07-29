/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:01:23 by ael-fari          #+#    #+#             */
/*   Updated: 2025/07/03 17:01:28 by ael-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_ast(t_ast *ast)
{
	if (!ast)
		return ;
	if (ast->type == NODE_COMMAND)
		free_string_array(ast->cmd.args);
	else if (ast->type == NODE_PIPE)
	{
		free_ast(ast->pipe.left);
		free_ast(ast->pipe.right);
	}
	else if (ast->type == NODE_REDIRECT)
	{
		free_ast(ast->redirect.command);
		free(ast->redirect.filename);
	}
	free(ast);
}

void	advance(t_lexer **lexer)
{
	if (*lexer)
		*lexer = (*lexer)->next;
}

t_ast	*parse(t_lexer **tokens)
{
	return (parse_pipeline(tokens));
}

// int	fill_cmd_utils(t_ast *node, t_cmd *cmd)
// {
// 	if (!node || !cmd)
// 		return (0);
// 	if (node->type == NODE_REDIRECT)
// 	{
// 		if (!fill_cmd(node->redirect.command, cmd))
// 			return (0);
// 		apply_redirect(cmd, node);
// 		return (1);
// 	}
// 	return (2);
// }

// int	fill_cmd(t_ast *node, t_cmd *cmd)
// {
// 	int	len;
// 	int	i;
// 	int	result;

// 	result = fill_cmd_utils(node, cmd);
// 	if (result != 2)
// 		return (result);
// 	else if (node->type == NODE_COMMAND)
// 	{
// 		len = 0;
// 		while (node->cmd.args && node->cmd.args[len])
// 			len++;
// 		cmd->args = malloc(sizeof(char *) * (len + 1));
// 		if (!cmd->args)
// 			return (0);
// 		i = -1;
// 		while (++i < len)
// 			cmd->args[i] = ft_strdup(node->cmd.args[i]);
// 		cmd->args[len] = NULL;
// 		return (1);
// 	}
// 	return (1);
// }


int	fill_cmd(t_ast *node, t_cmd *cmd)
{
	if (!node || !cmd)
		return (0);

	if (node->type == NODE_REDIRECT)
	{
		// Si commande présente, la remplir d'abord
		if (node->redirect.command)
		{
			if (!fill_cmd(node->redirect.command, cmd))
				return (0);
		}
		// Puis appliquer la redirection
		apply_redirect(cmd, node);
		return (1);
	}
	else if (node->type == NODE_COMMAND)
	{
		int len = 0;
		while (node->cmd.args && node->cmd.args[len])
			len++;
		cmd->args = malloc(sizeof(char *) * (len + 1));
		if (!cmd->args)
			return (0);
		for (int i = 0; i < len; i++)
			cmd->args[i] = ft_strdup(node->cmd.args[i]);
		cmd->args[len] = NULL;
		return (1);
	}
	return (1);
}