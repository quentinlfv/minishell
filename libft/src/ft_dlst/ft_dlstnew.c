/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasamadi <nasamadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:40:20 by nasamadi          #+#    #+#             */
/*   Updated: 2023/05/20 16:40:21 by nasamadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/ft_dlst.h>

t_dlist	*ft_dlstnew(void *data)
{
	t_dlist	*newdlst;

	newdlst = (t_dlist *)malloc(sizeof(t_dlist));
	if (!newdlst)
		return (NULL);
	newdlst->data = data;
	newdlst->next = NULL;
	newdlst->prev = NULL;
	return (newdlst);
}
