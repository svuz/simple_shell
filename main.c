#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"

int run(void)
{
    char input[MAX_COMMAND_LENGTH];
    while(1)
    {
        printf("$");
        
        // Read a command from the user
        
        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            perror("Failed to read input");
            exit;
        }
        size_t input_length = strlen(input);
        if (input_length > 0 && input[input_length - 1] == '\n') {
            input[input_length - 1] = '\0';
        }

        pid_t pid = fork();
        
        if (pid < 0) {
            perror("Fork failed");
            exit(1);
        } else if (pid == 0)
        {
            if (execve(input, (char *)NULL) == -1)
            {
                perror("Command execution failed");
                exit(1);
            }
        }
        else
        { 
            int status;
            wait(&status);
            
            if (WIFEXITED(status))
            {
                int exit_status = WEXITSTATUS(status);
                if (exit_status != 0) {
                    fprintf(stderr, "Command failed with exit status %d\n", exit_status);
                }
            }
        }
    }
    
    return (0);

}

int main() {
    run()
    return0 (0);
}