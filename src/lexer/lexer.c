#include <minishell.h>

t_lexer *new_word_token(t_lexer lexer, char cmd, int *i)
{
	int		start;

	start = i;
	while (ft_isalnum(cmd[*i]) && cmd[*i])
		(*i)++;
	if (start != *i)
		ft_lexadd_back(&lexer, ft_lexnew(ft_substr(cmd_line, start, *i - start), WORD));
	return (tmp);
}

t_lexer *token_recognition(char *cmd_line)
{
	t_lexer *lexer;
	int	i;

	lexer = NULL;
	i = 0;
	while (cmd_line[i])
	{
		lexer = new_word_token(lexer, cmd_line, &i)
	}
	return (lexer);
}

t_lexer *start_lexer(char *cmd_line)
{
	t_lexer	*lexer;

	lexer = token_recognition(cmd_line);
	return (lexer);
}
