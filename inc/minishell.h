#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

enum Token
{
	WORD,
	PIPE,
	WHITESPACE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	OPERATOR,
};

typedef struct s_lexer
{
	char *content;
	enum Token token;
	struct *t_lexer next;
} t_lexer;

# endif
