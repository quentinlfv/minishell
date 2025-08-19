/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 18:49:11 by ael-fari          #+#    #+#             */
/*   Updated: 2025/07/22 18:49:25 by ael-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_redir(t_cmd *cmd)
{
	if (cmd->infile || cmd->outfile)
		return (0);
	return (1);
}

int	make_exec_builtins_simple_command(t_cmd *cmd, t_env **envp, t_sig *sig)
{
	if (if_is_builtin(cmd) && check_redir(cmd))
	{
		execute_builtin(cmd, envp, sig);
		return (1);
	}
	return (0);
}

void	make_out_file_exec_pipeline_condition_next(int *fd_0,
		int *fd_1)
{
	close(*fd_0);
	dup2(*fd_1, STDOUT_FILENO);
	close(*fd_1);
}

void	make_out_file_exec_pipeline(t_cmd *cmd, int *fd_0, int *fd_1)
{
	int	out_fd;
	int	flags;

	if (cmd->outfile)
	{
		if (cmd->append)
			flags = O_WRONLY | O_CREAT | O_APPEND;
		else
			flags = O_WRONLY | O_CREAT | O_TRUNC;
		out_fd = open(cmd->outfile, flags, 0644);
		if (out_fd == -1)
		{
			perror(cmd->outfile);
			cmd->link->cmds = cmd;
			free_link_struct(*cmd->link);
			exit(127);
		}
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
	else if (cmd->next)
		make_out_file_exec_pipeline_condition_next(fd_0, fd_1);
}

int	handle_eof_signal(char *line)
{
	if (!line)
	{
		printf("exit\n");
		return (0);
	}
	return (1);
}
