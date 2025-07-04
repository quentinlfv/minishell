#include <../inc/minishell.h>

int	ft_strcmp(char *s1, char *s2)
{
	int i = 0;
	while (s1[i] == s2[i] && s1[i])
		i++;
	return ((int)s1[i] - (int)s2[i]);
}

char *getmyline(void)
{
	char *buf = NULL;

	if (buf)
	{
		free(buf);
		buf = NULL;
	}
	buf = readline("Prompt > ");
	return (buf);
}

// int	main(void)
// {
// 	t_lexer *lexer;
// 	char *rl;

// 	rl = NULL;	
// 	while ((rl = getmyline()) && ft_strcmp(rl, "exit") != 0)
// 	{
// 		printf("%s\n", rl);
// 		add_history(rl);
// 		lexer = start_lexer(rl);
// 		print_lex(lexer);
// 	}
// 	free(rl);
// 	return (0);
// }

int	main(void)
{
	t_lexer *lexer;
	t_ast *ast;
	char *rl = NULL;

	while ((rl = getmyline()) && ft_strcmp(rl, "exit") != 0)
	{
		printf("%s\n", rl);
		add_history(rl);
		lexer = start_lexer(rl);   // Ta fonction actuelle
		print_lex(lexer);          // Pour vérifier le lexing

		ast = parse(&lexer);       // 👈 Appel du parser
		if (ast)
			print_ast(ast, 0);     // 👈 Affichage de l'AST pour debug

		// free_ast(ast);         // ✅ À ajouter plus tard pour nettoyage
	}
	free(rl);
	return (0);
}
