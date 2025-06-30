#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minishell.h"
// ----------- Lexer Types -----------

// // ----------- AST Types -----------
// typedef enum e_node_type {
// 	NODE_COMMAND,
// 	NODE_PIPE,
// 	NODE_REDIRECT
// } t_node_type;

// typedef struct s_ast {
// 	t_node_type type;
// 	union {
// 		struct {
// 			char **args;
// 		} cmd;
// 		struct {
// 			struct s_ast *left;
// 			struct s_ast *right;
// 		} pipe;
// 		struct {
// 			struct s_ast *command;
// 			char *filename;
// 			t_token redirect_type;
// 		} redirect;
// 	};
// } t_ast;

// ----------- Lexer Utils -----------
void advance(t_lexer **lexer) {
	if (*lexer)
		*lexer = (*lexer)->next;
}

// ----------- Parser Functions -----------
char **parse_args(t_lexer **lexer) {
	int count = 0;
	t_lexer *tmp = *lexer;
	while (tmp && tmp->token == WORD) {
		count++;
		tmp = tmp->next;
	}

	char **args = malloc(sizeof(char *) * (count + 1));
	int i = 0;
	while (*lexer && (*lexer)->token == WORD) {
		args[i++] = strdup((*lexer)->content);
		advance(lexer);
	}
	args[i] = NULL;
	return args;
}

t_ast *parse_redirects(t_lexer **lexer) {
	t_ast *cmd = NULL;

	if (*lexer && (*lexer)->token == WORD) {
		cmd = malloc(sizeof(t_ast));
		cmd->type = NODE_COMMAND;
		cmd->cmd.args = parse_args(lexer);
	}

	while (*lexer && ((*lexer)->token == GREAT || (*lexer)->token == LESS ||
		(*lexer)->token == D_GREAT || (*lexer)->token == D_LESS)) {

		t_token redir_type = (*lexer)->token;
		advance(lexer);
		if (!*lexer || (*lexer)->token != WORD) {
			fprintf(stderr, "Syntax error: expected filename\n");
			return NULL;
		}
		t_ast *redir = malloc(sizeof(t_ast));
		redir->type = NODE_REDIRECT;
		redir->redirect.redirect_type = redir_type;
		redir->redirect.filename = strdup((*lexer)->content);
		redir->redirect.command = cmd;
		cmd = redir;
		advance(lexer);
	}
	return cmd;
}

t_ast *parse_pipeline(t_lexer **lexer) {
	t_ast *left = parse_redirects(lexer);
	while (*lexer && (*lexer)->token == PIPE) {
		advance(lexer);
		t_ast *right = parse_redirects(lexer);
		t_ast *pipe = malloc(sizeof(t_ast));
		pipe->type = NODE_PIPE;
		pipe->pipe.left = left;
		pipe->pipe.right = right;
		left = pipe;
	}
	return left;
}

t_ast *parse(t_lexer **tokens) {
	return parse_pipeline(tokens);
}

// ----------- Debug Functions -----------
void print_ast(t_ast *ast, int depth) {
	if (!ast) return;
	for (int i = 0; i < depth; i++) printf("  ");
	switch (ast->type) {
		case NODE_COMMAND:
			printf("COMMAND: ");
			for (int i = 0; ast->cmd.args[i]; i++)
				printf("%s ", ast->cmd.args[i]);
			printf("\n");
			break;
		case NODE_PIPE:
			printf("PIPE\n");
			print_ast(ast->pipe.left, depth + 1);
			print_ast(ast->pipe.right, depth + 1);
			break;
		case NODE_REDIRECT:
			printf("REDIRECT (%d): %s\n", ast->redirect.redirect_type, ast->redirect.filename);
			print_ast(ast->redirect.command, depth + 1);
			break;
	}
}

// Note: Tu dois encore ajouter ton propre lexer qui transforme une ligne de commande
// en liste `t_lexer*`, avec les bons `token` et `content`.

// Exemple d'utilisation (à compléter avec un vrai lexer)
// int main() {
// 	// Exemple de construction manuelle de la liste de tokens pour: cat < infile | grep hello > out.txt
// 	t_lexer t5 = {"out.txt", WORD, NULL, NULL};
// 	t_lexer t4 = {">", GREAT, &t5, NULL}; t5.prev = &t4;
// 	t_lexer t3 = {"hello", WORD, &t4, NULL}; t4.prev = &t3;
// 	t_lexer t2 = {"grep", WORD, &t3, NULL}; t3.prev = &t2;
// 	t_lexer t1b = {"|", PIPE, &t2, NULL}; t2.prev = &t1b;
// 	t_lexer t1a = {"infile", WORD, &t1b, NULL}; t1b.prev = &t1a;
// 	t_lexer t0 = {"<", LESS, &t1a, NULL}; t1a.prev = &t0;
// 	t_lexer t_start = {"cat", WORD, &t0, NULL}; t0.prev = &t_start;

// t_lexer *tokens = &t_start;
// 	t_ast *ast = parse(&tokens);
// 	print_ast(ast, 0);
// 	return 0;
// }
