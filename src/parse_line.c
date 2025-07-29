/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 21:12:27 by ael-fari          #+#    #+#             */
/*   Updated: 2025/07/02 21:12:29 by ael-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->append = 0;
	cmd->heredoc = 0;
	cmd->heredoc_fd = -1;
	cmd->heredoc_delimiter = NULL;
	cmd->next = NULL;
	cmd->previous = NULL;
	return (cmd);
}

static void	add_cmd_back(t_cmd **head, t_cmd *new_node)
{
	t_cmd	*tmp;

	if (!head || !new_node)
		return ;
	if (!*head)
	{
		*head = new_node;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
	new_node->previous = tmp;
}

void	handle_cmd_out_file(t_cmd *cmd, t_ast *node, int value_append)
{
	int	fd;

	if (cmd->outfile)
	{
		fd = open(cmd->outfile, O_TRUNC);
		if (fd > 0)
			close(fd);
		free(cmd->outfile);
	}
	cmd->outfile = strdup(node->redirect.filename);
	cmd->append = value_append;
}

void	apply_redirect(t_cmd *cmd, t_ast *node)
{
	if (!cmd || !node || node->type != NODE_REDIRECT)
		return ;
	if (node->redirect.redirect_type == GREAT)
	{
		handle_cmd_out_file(cmd, node, 0);
	}
	else if (node->redirect.redirect_type == D_GREAT)
	{
		handle_cmd_out_file(cmd, node, 1);
	}
	else if (node->redirect.redirect_type == LESS)
	{
		free(cmd->infile);
		cmd->infile = strdup(node->redirect.filename);
	}
	else if (node->redirect.redirect_type == D_LESS)
	{
		cmd->heredoc = 1;
		free(cmd->heredoc_delimiter);
		cmd->heredoc_delimiter = strdup(node->redirect.filename);
	}
}

// static int	fill_cmd(t_ast *node, t_cmd *cmd)
// {
// 	int	i;
// 	int	len;

// 	if (!node || !cmd)
// 		return (0);
// 	if (node->type == NODE_COMMAND)
// 	{
// 		len = 0;
// 		while (node->cmd.args && node->cmd.args[len])
// 			len++;
// 		cmd->args = malloc(sizeof(char *) * (len + 1));
// 		if (!cmd->args)
// 			return (0);
// 		i = -1;
// 		while (++i > -2 && i < len)
// 			cmd->args[i] = ft_strdup(node->cmd.args[i]);
// 		cmd->args[len] = NULL;
// 		return (1);
// 	}
// 	else if (node->type == NODE_REDIRECT)
// 	{
// 		// printf("ici\n");
// 		apply_redirect(cmd, node);
// 		if (node->redirect.redirect_type == D_LESS && !node->redirect.command)
// 			return (1);
// 		return (fill_cmd(node->redirect.command, cmd));
// 	}
// 	return (1);
// }

t_cmd	*ast_to_cmds(t_ast *node)
{
	t_cmd	*left_cmd;
	t_cmd	*right_cmd;
	t_cmd	*cmd;

	if (!node)
		return (printf("nul\n"), (NULL));
	if (node->type == NODE_PIPE)
	{
		left_cmd = ast_to_cmds(node->pipe.left);
		right_cmd = ast_to_cmds(node->pipe.right);
		add_cmd_back(&left_cmd, right_cmd);
		return (left_cmd);
	}
	else
	{
		cmd = new_cmd();
		if (!cmd)
			return (NULL);
		if (!fill_cmd(node, cmd))
		{
			free_cmd(cmd);
			return (NULL);
		}
		return (cmd);
	}
}
