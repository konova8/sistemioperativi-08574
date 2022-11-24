#define _GNU_SOURCE
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0666);

	switch (fork()) {
		case 0:
			write(fd, "prova erede\n", 12);
			exit(0);
		default:
			write(fd, "prova genitore\n", 15);
			break;
		case -1:
			exit(1);
	}
	int s;
	wait(&s);
}
