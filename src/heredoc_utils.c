/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 20:20:34 by ael-fari          #+#    #+#             */
/*   Updated: 2025/07/30 20:20:36 by ael-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	close_heredoc_fds_only(t_cmd *cmds)
{
	t_cmd	*tmp;

	tmp = cmds;
	while (tmp)
	{
		if (tmp->heredoc == 1 && tmp->infile)
		{
			close(tmp->heredoc_fd);
		}
		tmp = tmp->next;
	}
}

void	close_and_unlink_heredoc_fds(t_cmd *cmds)
{
	t_cmd	*tmp;

	tmp = cmds;
	while (tmp)
	{
		if (tmp->heredoc == 1 && tmp->infile)
		{
			if (tmp->heredoc_fd > 0)
				close(tmp->heredoc_fd);
			unlink(tmp->infile);
		}
		tmp = tmp->next;
	}
}

void	free_link_struct(t_link link)
{
	if (link.lexer)
		free_lexer(link.lexer, 0);
	if (link.env)
		free_env(link.env);
	if (link.cmds)
		free_cmd(link.cmds);
}

void	free_lexer_and_cmds(t_link link)
{
	free_lexer(link.lexer, 0);
	free_cmd(link.cmds);
}

t_link	init_link_struct(t_cmd *cmds, t_lexer *lexer, t_ast *ast, t_env **env)
{
	t_link	link;

	link.cmds = cmds;
	link.lexer = lexer;
	link.ast = ast;
	link.env = env;
	return (link);
}
