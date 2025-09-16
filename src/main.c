
#include "../include/minishell.h"

void	print_tokens(t_token *t)
{
	while (t)
	{
		if (t->type == WORD)
			printf("WORD: %s\n", t->value);
		else if (t->type == EOL)
			printf("EOL\n");
		t = t->next;
	}
}

void	free_tokenlist(t_token *tok)
{
	t_token	*next;

	while (tok)
	{
		next = tok->next;
		if (tok->value)
			free(tok->value);
		free(tok);
		tok = next;
	}
}

int	main(void)
{
	char	*line;
	t_token	*ts;

	// проверка на наличие только одного аргумента- программа минишел
	while (1)
	{
		line = readline("minishell % ");
		if (!line)
			break ;
		// Enter без текста → вернётся "" (пустая строка, но не NULL) а Ctrl- D → вернётся NULL, поэтому мы делаем брейк из цикла и после очищаем ресурсы такие как стракт
		// if (*line)
		// 	add_history(line);
		ts = tokenize(line);
		if (!ts)
		{
			// можно добавить сообщение об ошибке и вернуться на начало цикла чтобы получить линию и ее токенищировать
			free(line);
			continue ;
		}
		print_tokens(ts);
		free_tokenlist(ts);
		free(line);
	}
	// rl_clear_history();
	return (0);
}
