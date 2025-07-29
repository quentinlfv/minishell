#include "../inc/minishell.h"

void handle_signal_heredoc(int num)
{
	(void)num;
	// g_exit_status = 130;
	write(1, "\n", 1);
	// close(0);
	exit(130);
}

void set_signal_heredoc(void)
{
	signal(SIGINT, handle_signal_heredoc);
}

void	get_heredoc_fd(t_cmd *cmd, char *base, char *delimiter)
{

	cmd->infile = ft_strjoin(base, delimiter);
	cmd->heredoc_fd = open(cmd->infile, O_WRONLY | O_CREAT, 0644);
}

void close_heredoc_fds_only(t_cmd *cmds)
{
	t_cmd *tmp;

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

void close_and_unlink_heredoc_fds(t_cmd *cmds)
{
	t_cmd *tmp;

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
	free_lexer(link.lexer, 0);
	free_cmd(link.cmds);
	free_env(link.env);
}

void	free_lexer_and_cmds(t_link link)
{
	free_lexer(link.lexer, 0);
	free_cmd(link.cmds);
	// free_env(link.env);
}

t_link	init_link_struct(t_cmd *cmds, t_lexer *lexer, t_ast *ast, t_env **env)
{
	t_link link;

	link.cmds = cmds;
	link.lexer = lexer;
	link.ast = ast;
	link.env = env;
	return (link);
}

int	read_heredoc_input(int fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strcmp(line, delimiter))
			return (free(line), 1);
		// if (g_exit_status == 130)
		// 	return (free(line), 0);
		write(fd, line, strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	return (1);
}

void	hd_sig_parent(int num)
{
	(void)num;
	g_exit_status = 130;
}

int	run_heredoc_in_child(t_cmd *cmd, t_link link)
{
	t_sig	sig;

	sig.pid = fork();
    signal(SIGINT, hd_sig_parent);
	if (sig.pid == 0)
    {
        signal(SIGINT, handle_signal_heredoc);
		if (!read_heredoc_input(cmd->heredoc_fd, cmd->heredoc_delimiter))
			return (0);
		close_heredoc_fds_only(cmd);
		free_link_struct(link);
		// (void)link;
		// signal(SIGINT, handle_signal_heredoc);
        exit(0);
	}
		waitpid(sig.pid, &sig.exit_status, 0);
        if (WIFSIGNALED(sig.exit_status) && WTERMSIG(sig.exit_status) == SIGINT)
        {
            g_exit_status = 130;
			if (cmd->heredoc_fd > 0)
                close(cmd->heredoc_fd);
            if (cmd->infile)
                unlink(cmd->infile);
            return (0);
            printf("hello\n");
            free_lexer_and_cmds(link);
		}
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
	t_link link;
	t_cmd *tmp;

	link = init_link_struct(cmds, lexer, ast, env);
	tmp = cmds;
	while (tmp)
	{
		if (tmp->heredoc == 1)
		{
			get_heredoc_fd(tmp, "/tmp/.heredoc_",tmp->heredoc_delimiter);
			if (!run_heredoc_in_child(tmp, link))
				return (free_lexer_and_cmds(link), close_and_unlink_heredoc_fds(cmds), (0));
		}
		tmp = tmp->next;
	}
	return (1);
}