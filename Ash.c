#define  _GNU_SOURCE
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

// TODO these should be in header files
char* prompt(void);
char* get_pretty_wd(void);

/**
 * @brief Prompts the user for a command.
 *
 * @return The string that was entered by the user
 */
char* prompt(void)
{
	char* wd = get_pretty_wd();
	printf("Ash %s> ", wd);
	free(wd);

	/*
	 * TODO This currently limits the size of the command, it should realloc
	 * when reads more than 100 chars.
	 */
	char* buffer = malloc(100);

	if(buffer == NULL)
		return NULL;

	size_t i = 0;

	for(;;) {
		int c = fgetc(stdin);

		if (c == EOF) { /* Ctrl+d */
			free(buffer);
			return NULL;
		}

		if (c != '\n')
			buffer[i++] = c;
		else /* Enter pressed */
			break;
	}

	buffer[i] = '\0';
	return buffer;
}

/**
 * @brief Returns a formatted string of the current directory.
 *
 * @details Basically it substitutes the $HOME part of the current directory
 *          path string with a '~'.
 */
char* get_pretty_wd(void)
{
	char* cwd = get_current_dir_name();
	char* home = getenv("HOME");
	size_t hlen = strlen(home);

	/* checks if cwd starts with HOME */
	if (strncmp(cwd, home, hlen) == 0) {
		size_t cwdlen = strlen(cwd);
		cwd[0] = '~';
		memmove(cwd + 1, cwd + hlen, cwdlen - hlen + 1);
		cwd = realloc(cwd, cwdlen - hlen + 1);
	}

	return cwd;
}

int main(/*int argc, char** argv*/)
{
	char* cmd;

	do {
		char* args[] = {"", NULL};
		cmd = prompt();

		if (cmd != NULL && cmd[0] != '\0') {
			pid_t pid = fork();
			if (pid == 0) {
				/* Child process */
				if(execvp(cmd, args) == -1) {
					free(cmd);
					puts("Command failed");
					exit(1);
				}
			} else {
				/* Parent process waits for the executed process to terminate */
				waitpid(pid, NULL, 0);
			}
		}

		free(cmd);
	} while(cmd != NULL);
}
