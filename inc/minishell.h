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
	struct s_lexer *next;
	struct s_lexer *prev;
} t_lexer;


typedef enum e_node_type {
	NODE_COMMAND,
	NODE_PIPE,
	NODE_REDIRECT
} t_node_type;

typedef struct s_ast {
	t_node_type type;
	union {
		struct {
			char **args;
		} cmd;
		struct {
			struct s_ast *left;
			struct s_ast *right;
		} pipe;
		struct {
			struct s_ast *command;
			char *filename;
			t_token redirect_type;
		} redirect;
	};
} t_ast;



/* lexer */
void	new_ope_token(t_lexer **lexer, char **cmd);
void	new_word_token(t_lexer **lexer, char **cmd);
t_lexer *token_recognition(char *cmd);
t_lexer *start_lexer(char *cmd_line);
t_lexer	*new_token(char *content, t_token type);
t_lexer	*lex_last(t_lexer *lst);
void	add_token(t_lexer **lst, t_lexer *new);
void	print_lex(t_lexer *lexer);


void advance(t_lexer **lexer);
char **parse_args(t_lexer **lexer);
t_ast *parse_pipeline(t_lexer **lexer);
t_ast *parse_redirects(t_lexer **lexer);
t_ast *parse(t_lexer **tokens);
void print_ast(t_ast *ast, int depth);
# endif
