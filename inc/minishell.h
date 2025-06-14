#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"

typedef enum e_token
{
	WORD,
	PIPE,
	D_LESS, // <<
	D_GREAT, // >>
	LESS, // <
	GREAT, // >
} t_token;

typedef struct s_lexer
{
	char 		*content;
	t_token 	token;
	struct t_lexer *next;
	struct t_lexer *prev;
} t_lexer;


/* lexer */
void	new_ope_token(t_lexer **lexer, char **cmd);
void	new_word_token(t_lexer **lexer, char **cmd);
t_lexer *token_recognition(char *cmd);
t_lexer *start_lexer(char *cmd_line);
t_lexer	*new_token(void *content, t_token type);
t_lexer	*lex_last(t_lexer *lst);
void	add_token(t_lexer **lst, t_lexer *new);
void	print_lex(t_lexer *lexer);

# endif
