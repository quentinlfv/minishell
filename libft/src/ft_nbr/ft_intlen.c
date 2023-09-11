/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasamadi <nasamadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:43:05 by nasamadi          #+#    #+#             */
/*   Updated: 2023/05/20 16:44:30 by nasamadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/ft_nbr.h>

int	ft_intlen(int n)
{
	int	cnt;

	cnt = !n;
	while (n)
	{
		n /= 10;
		cnt++;
	}
	return (cnt);
}
