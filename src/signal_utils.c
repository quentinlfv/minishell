/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 20:21:10 by ael-fari          #+#    #+#             */
/*   Updated: 2025/07/30 20:21:12 by ael-fari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	hd_sig_parent(int num)
{
	(void)num;
	g_exit_status = 130;
}

void	handle_signal_heredoc(int num)
{
	(void)num;
	write(2, "\n", 1);
	close(0);
	g_exit_status = 130;
}

char	*get_pwd(void)
{
	char	cwd[1024];
	char	*pwd;

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		pwd = ft_strdup(cwd);
	else
		perror("pwd");
	return (pwd);
}

int	get_size_env(t_env **env)
{
	t_env	*tmp;
	int		size;

	size = 0;
	tmp = *env;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	return (size);
}
