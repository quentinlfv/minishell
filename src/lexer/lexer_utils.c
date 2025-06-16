#include <minishell.h>

t_lexer	*new_token(char *content, t_token type)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	lexer->content = content;
	lexer->token = type;
	lexer->next = NULL;
	lexer->prev = NULL;
	return (lexer);
}

t_lexer	*lex_last(t_lexer *lst)
{
	if (lst == NULL)
		return (lst);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	add_token(t_lexer **lst, t_lexer *new)
{
	t_lexer	*tmp;

	if (*lst == NULL)
		(*lst) = new;
	else
	{
		tmp = lex_last(*lst);
		tmp->next = new;
	}
}

void	print_lex(t_lexer *lexer)
{
	t_lexer *tmp;

	tmp = lexer;
	while (tmp)
	{
		printf("content = %s/// token = %d\n", tmp->content, tmp->token);
		tmp = tmp->next;
	}
}
