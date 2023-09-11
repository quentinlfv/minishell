/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstmap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasamadi <nasamadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:40:15 by nasamadi          #+#    #+#             */
/*   Updated: 2023/05/20 16:40:16 by nasamadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/ft_dlst.h>

t_dlist	*ft_dlstmap(t_dlist *dlst, void *(*f)(void *), void (*del)(void *))
{
	t_dlist	*new;
	t_dlist	*newdlst;

	if (!dlst || !f)
		return (NULL);
	newdlst = NULL;
	while (dlst)
	{
		new = ft_dlstnew(f(dlst->data));
		if (!new)
		{
			ft_dlstclear(&newdlst, del);
			return (NULL);
		}
		ft_dlstadd_back(&newdlst, new);
		dlst = dlst->next;
	}
	return (newdlst);
}
