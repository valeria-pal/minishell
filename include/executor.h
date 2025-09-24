#ifndef EXECUTOR_H
# define EXECUTOR_H

typedef struct s_cmd
{
	char **args;
	struct s_cmd *next;
} t_cmd;


#include "minishell.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include <errno.h>






# endif