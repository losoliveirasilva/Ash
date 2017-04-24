#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

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
	char* args[] = {"", NULL};
	char* cmd = prompt();

	if (cmd != NULL) {
		if (fork() == 0) {
			// Child process
			execvp(cmd, args);
		} else {
			// Parent process waits for the executed process to terminate
			wait(NULL);
		}
		free(cmd);
	}
}
