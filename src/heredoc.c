/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 20:20:18 by ael-fari          #+#    #+#             */
/*   Updated: 2025/07/30 20:20:20 by ael-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	get_heredoc_fd(t_cmd *cmd, char *base, char *delimiter)
{
	cmd->infile = ft_strjoin(base, delimiter);
	cmd->heredoc_fd = open(cmd->infile, O_WRONLY | O_CREAT, 0644);
}

int	read_heredoc_input(int fd, char *delimiter)
{
	char	*line;

	g_exit_status = 0;
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (g_exit_status == 130 || !ft_strcmp(line, delimiter))
			return (free(line), 1);
		write(fd, line, strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	return (1);
}

int	run_heredoc_in_child(t_cmd *cmd, t_link link)
{
	t_sig	sig;

	sig.pid = fork();
	signal(SIGINT, hd_sig_parent);
	if (sig.pid == 0)
	{
		signal(SIGINT, handle_signal_heredoc);
		read_heredoc_input(cmd->heredoc_fd, cmd->heredoc_delimiter);
		close_heredoc_fds_only(cmd);
		free_link_struct(link);
		exit(0);
	}
	waitpid(sig.pid, 0, 0);
	if (g_exit_status == 130)
		return (close(cmd->heredoc_fd), unlink(cmd->infile), 0);
	else
	{
		if (cmd->heredoc_fd > 0)
			close(cmd->heredoc_fd);
		cmd->heredoc_fd = open(cmd->infile, O_RDONLY);
	}
	return (1);
}

int	prepare_heredoc(t_cmd *cmds, t_lexer *lexer, t_ast *ast, t_env **env)
{
	t_link	link;
	t_cmd	*tmp;

	link = init_link_struct(cmds, lexer, ast, env);
	tmp = cmds;
	while (tmp)
	{
		if (tmp->heredoc == 1)
		{
			get_heredoc_fd(tmp, "/tmp/.heredoc_", tmp->heredoc_delimiter);
			if (!run_heredoc_in_child(tmp, link))
				return (close_and_unlink_heredoc_fds(cmds),
					free_lexer_and_cmds(link), (0));
		}
		tmp = tmp->next;
	}
	return (1);
}
