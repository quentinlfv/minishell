/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasamadi <nasamadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:56:01 by nasamadi          #+#    #+#             */
/*   Updated: 2023/06/27 13:11:53 by nasamadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

/* redirection pipe and handle redirection for io */
static void	redir_pipe_io(t_cmd *cmd, t_bool is_parent, int fd_io[2])
{
	if (cmd->io->is_pipe[FD_IN] == TRUE && !is_parent)
		dup2(cmd->io->fd_read, STDIN_FILENO);
	if (cmd->io->is_pipe[FD_OUT] == TRUE)
		dup2(cmd->io->fd_pipe[WRITE_END], STDOUT_FILENO);
	if (!is_parent && (cmd->io->is_pipe[FD_IN] || cmd->io->is_pipe[FD_OUT]))
	{
		close(cmd->io->fd_pipe[READ_END]);
		close(cmd->io->fd_pipe[WRITE_END]);
		close(cmd->io->fd_read);
	}
	if (fd_io[FD_IN] >= 0 && !is_parent)
	{
		dup2(fd_io[FD_IN], STDIN_FILENO);
		close(fd_io[FD_IN]);
	}
	if (fd_io[FD_OUT] >= 0)
	{
		dup2(fd_io[FD_OUT], STDOUT_FILENO);
		close(fd_io[FD_OUT]);
	}
}

/* handle type and redir node */
static int	handle_redir_node(t_ast *redir, int fd_io[2])
{
	int	type;

	type = ast_gettype(redir);
	if ((type & AST_RD_TRUNC && redir_trunc(redir, fd_io) == 1)
		|| (type & AST_RD_APPEND && redir_append(redir, fd_io) == 1)
		|| (type & AST_RD_INFILE && redir_infile(redir, fd_io) == 1)
		|| (type & AST_RD_HDOC && redir_heredoc(redir, fd_io) == 1))
	{
		return (1);
	}
	return (0);
}

/* Close file descriptors */
static void	close_fds(int fd_io[2])
{
	if (fd_io[FD_IN] != -1)
		close(fd_io[FD_IN]);
	if (fd_io[FD_OUT] != -1)
		close(fd_io[FD_OUT]);
}

/* handle type and redir node within io redirection */
static int	handle_redir_node_and_io(t_cmd *cmd, t_bool is_parent)
{
	int		fd_io[2];
	t_ast	*redir;

	fd_io[0] = -1;
	fd_io[1] = -1;
	redir = cmd->io->redir;
	while (redir != NULL)
	{
		if (handle_redir_node(redir, fd_io) == 1)
		{
			close_fds(fd_io);
			return (1);
		}
		redir = redir->left;
	}
	redir_pipe_io(cmd, is_parent, fd_io);
	return (0);
}

/* handle redirections for command */
int	redir_cmd(t_cmd *cmd, t_bool is_parent)
{
	int	status;

	status = handle_redir_node_and_io(cmd, is_parent);
	if (status != 0)
	{
		g_sh.status = 1;
		return (status);
	}
	return (0);
}
