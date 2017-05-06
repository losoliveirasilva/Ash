#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <pwd.h>
#include <string.h>

const char *getUserDir()
{
	char *username;
	uid_t uid = geteuid();
	struct passwd *pw = getpwuid(uid);

	if (pw) {
		username = malloc(strlen(pw->pw_name));
		strcpy(username, pw->pw_dir);
		return username;
	}

	return "";
}

char* prompt(char* dir)
{
	printf("Ash %s> ", dir);

	/*
	 * TODO This currently limits the size of the command, it should realloc
	 * when reads more than 100 chars.
	 */
	char* line = malloc(100);

	if(line == NULL)
		return NULL;

	size_t i = 0;
	int c;

	for(;;) {
		if ((c = fgetc(stdin)) == EOF) /* Ctrl+d */
			return NULL;

		if (c != '\n')
			line[i++] = c;
		else /* Enter pressed */
			break;
	}

	line[i] = '\0';
	return line;
}

char* getCurrDir()
{
	int slashcount = 0;
	unsigned int i = 0;

	char buff[100 + 1];
	char* cwd = getcwd( buff, 100 + 1 );

	if( cwd != NULL ) {
		for(; i < strlen(cwd); ++i)
			if(cwd[i] == '/' && slashcount++ == 2)
				break;
	}

	char* aux = malloc(i);
	memmove(aux, cwd, i);
	aux[i] = '\0';

	char* userdir = malloc(strlen(getUserDir()));
	strcpy(userdir, getUserDir());

	if(strcmp(aux, userdir) == 0) {
		char* dirWithTilde = malloc(strlen(cwd)-1);
		dirWithTilde[0] = '~';
		memmove(dirWithTilde+1, cwd+i, strlen(cwd)-i);
		return dirWithTilde;
	}

	return cwd;
}

int main(/*int argc, char** argv*/)
{
	char* cmd;

	do {
		char* args[] = {"", NULL};
		cmd = prompt(getCurrDir());

		if (cmd != NULL && cmd[0] != '\0') {
			pid_t pid = fork();
			if (pid == 0) {
				/* Child process */
				if(execvp(cmd, args) == -1) {
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
