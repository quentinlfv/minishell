#include <minishell.h>

t_lexer	*ft_lexnew(void *content, t_token type)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	if (!list)
		return (NULL);
	lexer->content = content;
	lexer->token = type;
	lexer->next = NULL;
	lexer->prev = NULL;
	return (lexer);
}

t_lexer	*ft_lexlast(t_lexer *lst)
{
	if (lst == NULL)
		return (lst);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lexadd_back(t_lexer **lst, t_lexer *new)
{
	t_lexer	*tmp;

	if (*lst == NULL)
		(*lst) = new;
	else
	{
		tmp = ft_lstlast(*lst);
		tmp->next = new;
	}
}

void	ft_print_lex(t_lexer *lexer)
{
	t_lexer *tmp;

	tmp = lexer;
	while (lexer-> != NULL)
	{
		printf("content = %s\n", lexer->content);
		lexer = lexer->next;
	}
}
