#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	int fd_dir = open(".", O_DIRECTORY | O_RDONLY);
	chdir(argv[1]);
	char *new = getcwd(NULL, 0);
	printf("%s\n", new);
	fchdir(fd_dir);
	char *actual = getcwd(NULL, 0);
	printf("%s\n", actual);
	free(new);
	free(actual);
}
