#include <minishell.h>

t_lexer *new_word_token(t_lexer lexer, char cmd, int *i)
{
	int		start;

	start = i;
	while (ft_isalnum(cmd[*i]) && cmd[*i])
		(*i)++;
	if (start != *i)
		lex_add_back(&lexer, ft_lexnew(ft_substr(cmd_line, start, *i - start), WORD));
	return (tmp);
}

t_lexer *token_recognition(char *cmd_line)
{
	t_lexer *lexer;
	int	start;
	int	current;

	lexer = NULL;
	current = 0;
	start = current;
	while (cmd_line[current])
	{
		if (ft_is_space(cmd_line[current]))
		{
			lex_add_back(&lexer, lex_new(ft_substr(cmd_line, start, current - start), WORD));
			start = current + 1;	
		}
		else if (ft_is_symbol(cmd_line[current]))
		{
			lex_add_back(&lexer, lex_new(ft_substr(cmd_line, start, current - start), OPERATOR));
			start = current + 1;
		}
		else if (cmd_line[current] == '\0')
			lex_add_back(&lexer, lex_new(ft_substr(cmd_line, start, current - start), WORD));
	}
	return (lexer);
}

t_lexer *start_lexer(char *cmd_line)
{
	t_lexer	*lexer;

	lexer = token_recognition(cmd_line);
	return (lexer);
}
