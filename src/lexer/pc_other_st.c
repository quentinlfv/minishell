/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pc_other_st.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasamadi <nasamadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:54:32 by nasamadi          #+#    #+#             */
/*   Updated: 2023/06/15 14:31:16 by nasamadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

/* on other states */
void	handle_other_st(t_lexsup *ls)
{
	if (ls->st == ST_IN_QUOTE)
	{
		ls->tok->data[ls->j++] = ls->c;
		if (ls->type == CHAR_QOUTE)
			ls->st = ST_GEN;
	}
	else if (ls->st == ST_IN_DQUOTE)
	{
		ls->tok->data[ls->j++] = ls->c;
		if (ls->type == CHAR_DQOUTE)
			ls->st = ST_GEN;
	}
	else if (ls->st == ST_IN_CURLY)
	{
		ls->tok->data[ls->j++] = ls->c;
		if (ls->type == CHAR_CCL)
			ls->st = ST_GEN;
	}
}
