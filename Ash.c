#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/wait.h>

char* prompt(void) {
	printf("Ash> ");

	// TODO This currently limits the size of the command, it should realloc
	// when reads more than 100 chars.
	char* line = malloc(100);
	size_t i = 0;
	int c;

	if(line == NULL)
		return NULL;

	for(;;) {

		if ((c = fgetc(stdin)) == EOF) // Ctrl+d
			return NULL;

		if (c != '\n')
			line[i++] = c;
		else // Enter pressed
			break;

	}

	line[i+1] = '\0';
	return line;
}

int main(/*int argc, char** argv*/) {
	char* cmd;

	do {

		char* args[] = {"", NULL};
		cmd = prompt();

		if (cmd != NULL && cmd[0] != '\0') {
			pid_t pid = fork();
			if (pid == 0) {
				// Child process
				if(execvp(cmd, args) == -1) {
					puts("Command failed");
					exit(1);
				}
			} else {
				// Parent process waits for the executed process to terminate
				waitpid(pid, NULL, 0);
			}
		}

		free(cmd);

	} while(cmd != NULL);
}
