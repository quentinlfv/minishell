#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef enum e_token
{
	WORD,
	PIPE,
	NEWLINE,
	DLESS, // <<
	DGREAT, // >>
	LESS, // <
	GREAT, // >
} t_token;

typedef struct s_lexer
{
	char 		*content;
	struct t_token token;
	struct *t_lexer next;
	struct *t_lexer prev;
} t_lexer;


/* lexer */
t_lexer	*ft_lexnew(void *content, t_token type);
void	ft_lexadd_back(t_lexer **lst, t_lexer *new);

# endif
