/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasamadi <nasamadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:48:40 by nasamadi          #+#    #+#             */
/*   Updated: 2023/05/20 16:48:41 by nasamadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/ft_str.h>

void	ft_striter(char *s, void (*f)(char *))
{
	if (!s || !f)
		return ;
	while (*s)
		f(s++);
}
