/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 12:13:18 by vpaliash          #+#    #+#             */
/*   Updated: 2025/11/15 10:23:06 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"


//test for signals
/* int	main(void) // test for signals
{
	set_termios();
	setup_signals();
	prompt();
	return (0);
} */

// test for non built ins,
// test for executor for raw_data_

int	main(int argc, char **argv, char *const envp[])
{
	(void)argc;
	(void)argv;
	t_command *cmd;
	int status;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (1);

	cmd->next = NULL;
	cmd->argv = malloc(2 * sizeof(char *));
	cmd->argv[0] = ft_strdup("cat");
	cmd->argv[1] = NULL;
	status = execute(cmd, envp);
	if (status == 0)
		printf("success\n");
	else
		printf("%s: command not found\n", cmd->argv[0]);
	free(cmd->argv[0]);
	free(cmd->argv);
	free(cmd);
	return (0);
}

//test for redirections
// int	main(void)
// {
// 	t_command		cmd;
// 	t_redirection	redir;
// 	char			*argv_echo[] = {"echo", "a", NULL};
// 	char			*argv_cat[] = {"cat", NULL};

// 	//TEST 1: echo a > out.txt
// 	redir.type = R_OUT;
// 	redir.filename = "out.txt";
// 	redir.next = NULL;
// 	cmd.argv = argv_echo;
// 	cmd.redirs = &redir;
// 	cmd.next = NULL;

// 	printf("Running: echo a > out.txt\n");
// 	pid_t pid = fork();
// 	if (pid == 0)
// 	{
// 		apply_redirections_to_cmd(&cmd);
// 		execve("/bin/echo", cmd.argv, NULL);
// 		perror("execve");
// 		_exit(1);
// 	}
// 	waitpid(pid, NULL, 0);

// 	// TEST 2: cat < out.txt
// 	redir.type = R_IN;
// 	redir.filename = "out.txt";
// 	cmd.argv = argv_cat;
// 	cmd.redirs = &redir;
// 	cmd.next = NULL;

// 	printf("Running: cat < out.txt\n");
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		apply_redirections_to_cmd(&cmd);
// 		execve("/bin/cat", cmd.argv, NULL);
// 		perror("execve");
// 		_exit(1);
// 	}
// 	waitpid(pid, NULL, 0);

// 	return (0);
// }


