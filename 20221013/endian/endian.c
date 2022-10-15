#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
	int fd;
	int val;
	switch (argc) {
		case 2:
			fd = open(argv[1], O_RDONLY);
			read(fd, &val, sizeof(val));
			printf("%d %x\n",val,val);
			close(fd);
			break;
		case 3:
			val = strtol(argv[1], NULL, 0);
			fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
			write(fd, &val, sizeof(val));
			close(fd);
			break;
		default:
			printf("ERR\n");
			return 1;
	}
	return 0;
}


