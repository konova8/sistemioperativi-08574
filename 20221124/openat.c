#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	int fd_dir = open("/etc", O_PATH);
	int fd = openat(fd_dir, argv[1], O_RDONLY);
	char buf[1024];
	int n;
	while((n = read(fd, buf, 1024)) > 0)
		write(STDOUT_FILENO, buf, n);
	close(fd);
	close(fd_dir);
}
