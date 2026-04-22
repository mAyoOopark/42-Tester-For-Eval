#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int	sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
	int stsus;
	pid_t pid;

	pid = fork();
	if(pid == -1)
		return (-1);
	if(pid == 0) {
		alarm(timeout);
		f();
		exit(0);
	}

	waitpid(pid, &stsus, 0);
	if(WIFEXITED(stsus)) {
		if(WEXITSTATUS(stsus) == 0) {
			if(verbose) printf("Nice function!\n");
			return (1);
		}
		if(verbose) printf("Bad function: exited with code %d\n", WEXITSTATUS(stsus));
		return (0);
	}
	if(WIFSIGNALED(stsus)) {
		if(WTERMSIG(stsus) == SIGALRM) {
			if(verbose) printf("Bad function: timed out after %u seconds\n", timeout);
		} else {
			if(verbose) printf("Bad function: %s\n", strsignal(WTERMSIG(stsus)));
		}
		return (0);
	}

	return (-1);
}