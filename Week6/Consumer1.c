#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#define FIFO_NAME "/tmp/my_fifo"
int main()
{
	int pipe_fd;
	int res;
	int open_mode = O_RDONLY;
	char buffer[256];
	int bytes_read = 0;
	printf("Process %d opening FIFO O_RDONLY\n", getpid());
	pipe_fd = open(FIFO_NAME, open_mode);
	printf("Process %d result %d\n", getpid(), pipe_fd);
	if (pipe_fd != -1) {
		int i=0;
		while(i < 4){
		sleep(1);
		res = read(pipe_fd, buffer, sizeof(buffer));
		printf("%d,%s\n",res,buffer);
		bytes_read += res;
		i++;
		};
		close(pipe_fd);
	}
	else {
	exit(EXIT_FAILURE);
	}
	printf("Process %d finished, %d bytes read\n", getpid(), bytes_read);
	exit(EXIT_SUCCESS);
}