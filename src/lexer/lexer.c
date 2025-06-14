#include <minishell.h>

void	new_ope_token(t_lexer **lexer, char **cmd)
{
	if (**cmd == '>')
	{
		if (**cmd + 1 == '>')
		{
			add_token(lexer, new_token(">>", D_GREAT));
			(*cmd)++;
		}
		else
			add_token(lexer, new_token(">", GREAT));
	}
	else if (**cmd == '<')
	{
		if (**cmd + 1 == '<')
		{
			add_token(lexer, new_token("<<", D_LESS));
			(*cmd)++;
		}
		else
			add_token(lexer, new_token("<", LESS));
	}
	else if (**cmd == '|')
		add_token(lexer, new_token("|", PIPE));
	(*cmd)++;
}

void	new_word_token(t_lexer **lexer, char **cmd)
{
	int		quote;
	int		idx;

	quote = 0;
	idx = 0;
	while (ft_strchr(" \t\n<>|", *cmd[idx]))
	{
		if (quote == 0 && ft_strchr("'\"", *cmd[idx]))
			quote = *cmd[idx];
		else if (quote != 0 && quote == *cmd[idx])
			quote = 0;
		idx++;
	}
	add_token(lexer, new_token(ft_substr(*cmd, 0, idx), WORD));
	(*cmd) = (*cmd) + idx;
}

t_lexer *token_recognition(char *cmd)
{
	t_lexer *lexer;

	lexer = NULL;
	while (*cmd)
	{
		while (ft_strchr(" \t\n", *cmd) && *cmd)
			cmd++;
		if (ft_strchr("<>|", *cmd))
			new_ope_token(&lexer, &cmd);
		else
			new_word_token(&lexer, &cmd);
	}
	return (lexer);
}

t_lexer *start_lexer(char *cmd_line)
{
	t_lexer	*lexer;

	lexer = token_recognition(cmd_line);
	return (lexer);
}
