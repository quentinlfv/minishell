/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasamadi <nasamadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:56:55 by nasamadi          #+#    #+#             */
/*   Updated: 2023/06/29 15:36:11 by nasamadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void	print_pwd(const char *pwd)
{
	write(STDOUT_FILENO, pwd, ft_strlen(pwd));
	write(STDOUT_FILENO, "\n", 1);
}

int	ft_get_wdir(char **n)
{
	char	*pwd;
	int		should_free;

	pwd = (char *)malloc(sizeof(char) * PATH_MAX);
	should_free = 1;
	if (!pwd)
		return (1);
	(void)n;
	if (getcwd(pwd, PATH_MAX) == NULL)
	{
		free(pwd);
		pwd = ft_getenv("PWD");
		should_free = 0;
	}
	if (pwd == NULL)
		return (1);
	print_pwd(pwd);
	if (should_free)
		free(pwd);
	return (0);
}
