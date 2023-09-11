/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasamadi <nasamadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:52:35 by nasamadi          #+#    #+#             */
/*   Updated: 2023/06/15 14:31:16 by nasamadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

/* open rc file */
static int	open_rc(void)
{
	char	*home;
	char	*file;
	int		fd;

	home = ft_getenv("HOME");
	if (home == NULL)
		return (-1);
	file = dir_join(home, RC_FILE);
	free(home);
	if (access(file, R_OK))
	{
		free(file);
		return (-1);
	}
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		free(file);
		return (-1);
	}
	free(file);
	return (fd);
}

/* read config from .minishrc */
void	read_config(void)
{
	char	*line;
	int		fd;

	fd = open_rc();
	if (fd == -1)
		return ;
	line = ft_get_next_line(fd);
	while (line != NULL)
	{
		handle_line(line, TRUE);
		line = ft_get_next_line(fd);
	}
	close(fd);
}
