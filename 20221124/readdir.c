#define _GNU_SOURCE
#include <dirent.h>     /* Defines DT_* constants */
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/syscall.h>

#define handle_error(msg) \
	do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main(int argc, char *argv[])
{
	DIR *d = opendir(argc > 1 ? argv[1] : ".");
	if (d == NULL)
		handle_error("open");

	for (;;) {
		struct dirent *de = readdir(d);
		if (de == NULL)
			break;
		printf("%8ld  ", de->d_ino);
		printf("%-10s ", (de->d_type == DT_REG) ?  "regular" :
				(de->d_type == DT_DIR) ?  "directory" :
				(de->d_type == DT_FIFO) ? "FIFO" :
				(de->d_type == DT_SOCK) ? "socket" :
				(de->d_type == DT_LNK) ?  "symlink" :
				(de->d_type == DT_BLK) ?  "block dev" :
				(de->d_type == DT_CHR) ?  "char dev" : "???");
		printf("%s\n", de->d_name);
	}
	closedir(d);

	exit(EXIT_SUCCESS);
}
