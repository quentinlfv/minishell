/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 20:40:24 by ael-fari          #+#    #+#             */
/*   Updated: 2025/07/25 20:40:44 by ael-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_exit(t_cmd *cmds)
{
	t_cmd	*cmd;

	cmd = cmds;
	if (cmds->heredoc_delimiter)
		return (0);
	while (cmd)
	{
		if (!ft_strcmp(cmd->args[0], "exit"))
		{
			if (builtin_exit(cmds) != -100)
				return (1);
		}
		cmd = cmd->next;
	}
	return (0);
}
