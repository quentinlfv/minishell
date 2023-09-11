/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasamadi <nasamadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:54:51 by nasamadi          #+#    #+#             */
/*   Updated: 2023/06/15 14:31:16 by nasamadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

/* rejoin a token list */
void	rejoin_tokens(t_tok **tok, t_tok **prev, t_lexer *lex, t_tok *head)
{
	int		cnt;
	t_tok	*aux;

	aux = head;
	cnt = 1;
	while (aux->next && ++cnt)
		aux = aux->next;
	aux->next = (*tok)->next;
	if (lex->tok_lst == *tok)
		lex->tok_lst = head;
	else
		(*prev)->next = head;
	free((*tok)->data);
	free(*tok);
	lex->n_toks += cnt;
	*tok = aux->next;
	*prev = aux;
}

/* rejoin a token list and remain at same pos */
void	insert_toklst(t_tok **tok, t_tok **prev, t_lexer *lex, t_tok *head)
{
	int		cnt;
	t_tok	*aux;

	aux = head;
	cnt = 1;
	while (aux->next && ++cnt)
		aux = aux->next;
	aux->next = (*tok)->next;
	if (lex->tok_lst == *tok)
		lex->tok_lst = head;
	else
		(*prev)->next = head;
	free((*tok)->data);
	free(*tok);
	lex->n_toks += cnt;
	*tok = head;
}
