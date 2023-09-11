/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasamadi <nasamadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:55:51 by nasamadi          #+#    #+#             */
/*   Updated: 2023/06/29 13:37:55 by nasamadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/* search command in path */
static char	*get_path(char *cmd, const char *path)
{
	char	*file;
	char	*dir;
	int		diff;

	while (*path)
	{
		diff = ft_strchr(path, ':') - path;
		if (diff < 0)
			diff = ft_strlen(path);
		dir = ft_substr(path, 0, diff);
		file = dir_join(dir, cmd);
		free(dir);
		if (access(file, X_OK) == 0)
			return (file);
		free(file);
		if (ft_strlen(path) < (size_t)diff)
			break ;
		path += diff;
		if (*path)
			path++;
	}
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	exit(127);
	return (NULL);
}

/* check and validate command */
static void	validate_exec(t_exec *e)
{
	if (stat(e->cmd_path, &e->st) != 0)
	{
		ft_putstr_fd(e->cmd_path, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		exit(127);
	}
	else if (S_ISDIR(e->st.st_mode))
	{
		ft_putstr_fd(e->cmd_path, STDERR_FILENO);
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
		exit(126);
	}
	else if (access(e->cmd_path, X_OK) != 0)
	{
		ft_putstr_fd(e->cmd_path, STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		exit(126);
	}
}

static void	handle_path(t_exec *e)
{
	e->path = ft_getenv("PATH");
	if (e->path == NULL)
	{
		ft_putstr_fd(e->cmd->argv[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exit(127);
	}
	e->cmd_path = get_path(e->cmd->argv[0], e->path);
}

static void	handle_cmd_path(t_exec *e)
{
	if (*e->cmd->argv[0] == '/' || !ft_strncmp(e->cmd->argv[0], "~/", 2)
		|| !ft_strncmp(e->cmd->argv[0], "./", 2)
		|| !ft_strncmp(e->cmd->argv[0], "../", 3))
		e->cmd_path = e->cmd->argv[0];
	else
		handle_path(e);
}

void	find_and_exec_cmd(t_cmd *cmd)
{
	t_exec	e;

	e.cmd = cmd;
	handle_cmd_path(&e);
	validate_exec(&e);
	execve(e.cmd_path, e.cmd->argv, get_env_char());
	perror_exit(e.cmd_path);
}
