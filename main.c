#include "main.h"
/**
 * ecmd - creates a procs son
 * @extstus: exit status
 * @fpt: executable command
 * @tokens: array of arguments passed
 * Return: void
 */
int ecmd(int *extstus, char *fpt, char *tokens[])
{
	pid_t child;
	int status;

	child = fork();
	if (child == -1)
	{
		perror("fork");
		return (1);
	} /* end if */
	if (child == 0)
	{
		execve(fpt, tokens, environ);
		*extstus = 2;
		perror("execve");
		exit(*extstus);
	} /* end if */
	else
	{
		wait(&status);
		if (WIFEXITED(status))
		{
			*extstus = WEXITSTATUS(status);
		} /* end if */
	} /* end else */
	if (fpt != tokens[0])
		free(fpt);
	return (0);
} /* end function */

/**
 * hept - prints prompt and gets input
 * @lgth: lgth of put
 * @line: input stored
 */
int hept(size_t *lgth, char **line)
{
	ssize_t bytes_read;
	char newline = '\n';
	int is_interactive = isatty(STDIN_FILENO);

	if (is_interactive)
	{
		write(STDOUT_FILENO, "$ ", 2);
	} /* end if */
	bytes_read = getline(line, lgth, stdin);
	if (bytes_read == -1)
	{
		if (is_interactive)
		{
			write(STDOUT_FILENO, &newline, 1);
		} /* end if */
	return (1);
	} /* end if */
	return (0);
} /* end function */

/**
 * check_builtins - check for builtins
 *
 * @tnc: passed arguments
 * @tokens: shell's list
 * @argv: argument array
 * @extstus: exit status
 */
int chbui(int tnc, char **tkns, int *extstus, char **argv)
{
	char **env = environ;
	char newline = '\n';

	if (tnc < 1)
	{
		return (2);
	}
	if (strcmp(tkns[0], "exit") == 0)
	{
		if (tkns[1] != NULL)
		{
			if (convertStringToInt(tkns[1]))
				if (convertStringToInt(tkns[1]) >= 0)
					*extstus = convertStringToInt(tkns[1]);
				else
					error_message(tkns, argv, extstus);
			else
			{
				error_message(tkns, argv, extstus);
			}
		}
		return (1);
	}
	if (strcmp(tkns[0], "env") == 0)
	{
		env = environ;
		while (*env != NULL)
		{
			write(STDOUT_FILENO, *env, strlen(*env));
			write(STDOUT_FILENO, &newline, 1);
			env++;
		}
		return (2);
	}
	if (strcmp(tkns[0], "unsetenv") == 0)
	{
		unsetEnvironmentVariable(tkns[1]);
		return (2);
	}
	return (0);
}



/**
 * _pk - checks for executable file errors
 * @argv: command line argument list
 * @tokens: array of user input
 * @fpt: full path of command inputed
 * @extstus: exit status
 * Return: void
 */
int _pk(char **argv, char **tokens, char **fpt, int *extstus)
{
	char newline = '\n';
	char *path = getEnvironmentVariable("PATH");

	if (access(tokens[0], X_OK) == -1)
	{
		*fpt = findfpt(tokens[0], path);
		if (access(*fpt, X_OK) == -1)
		{
			write(STDERR_FILENO, argv[0], strlen(argv[0]));
			write(STDERR_FILENO, ": 1: ", 5);
			write(STDERR_FILENO, tokens[0], strlen(tokens[0]));
			write(STDERR_FILENO, ": Illegal number:", 11);
			write(STDERR_FILENO, &newline, 1);
			*extstus = 127;
			return (2);
		}
	} 

	return (0);
}
/**
 * main - simple shell
 * @argv: argument list
 * @argc: argument count
 * Return: exit status
 */
int main(int argc __attribute__((unused)), char **argv)
{
	char *line = NULL;
	size_t length = 0;
	char *tokens[buffer];
	int cnt, result;
	char *fpt;
	int extstus = 0;

	while (1)
	{
		result = hept(&length, &line);
		if (result == 1)
			break; /* end  if */
		cnt = 0;
		tokens[cnt] = strtok(line, " \t\n");
		while (tokens[cnt] != NULL)
		{
			cnt++;
			tokens[cnt] = strtok(NULL, " \t\n");
		} /* end while */
		tokens[cnt] = NULL;
		fpt = tokens[0];
		result = check_builtins(cnt, tokens, &extstus, argv);
		if (result == 1)
			break; /* end if */
		else if (result == 2)
			continue; /* end else if */
		result = _ch(argv, tokens, &fpt, &extstus);
		if (result == 1)
			break;/* end if */
		else if (result == 2)
			continue; /* else if */
		result = exec_command(&extstus, fpt, tokens);
		if (result == 1)
			break; /* end if */
		else if (result == 2)
			continue; /*end if*/
	} /* End while */
	free(line);
	return (extstus);
} /* end function */