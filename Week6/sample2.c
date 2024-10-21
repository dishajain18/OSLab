#include <sys/wait.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int pfd[2];
	pid_t cpid;
	char buf;
	assert(argc == 2);

	if (pipe(pfd) == -1) 
		{ perror("pipe");
	      exit(-1); }
	cpid = fork();
	if (cpid == -1) 
		{ perror("fork");
	      exit(-1); }

	if (cpid == 0) 
		{ /* Child reads from pipe */
		close(pfd[1]);
		/* Close unused write end */
		while (read(pfd[0], &buf, 1) > 0)
		write(1, &buf, 1);
		write(1, "\n", 1);
		close(pfd[0]);
		exit(0);
		} 

	else {
		/* Parent writes argv[1] to pipe */
		close(pfd[0]);
		/* Close unused read end */
		write(pfd[1], argv[0], strlen(argv[0]));
		close(pfd[1]);
		/* Reader will see EOF */
		wait(NULL);
		/* Wait for child */
		exit(0);
		}
}