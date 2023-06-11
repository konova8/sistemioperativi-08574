#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(int argv, char *argc[])
{
	int num_child = 2;
	char* pathname1 = argc[1];
	char* pathname2 = argc[2];

	if (argv > 3 && strcmp(argc[1], "-j") == 0)
	{
		num_child = atoi(argc[2]);
		pathname1 = argc[3];
		pathname2 = argc[4];
	}
	int fd1 = open(pathname1, O_RDONLY);
	int fd2 = open(pathname2, O_RDONLY);

	struct stat st;
	stat(pathname1, &st);
	off_t fsize1 = st.st_size;
	stat(pathname2, &st);
	off_t fsize2 = st.st_size;
	if (fsize1 != fsize2)
	{
		printf("%s %s differ\n", pathname1, pathname2);
		return 0;
	}

	int p_ids[num_child];
	off_t delta = fsize1 / num_child;
	off_t start = 0;
	
	// printf("src1_size: %ld\n", src1_size);
	// printf("src2_size: %ld\n", src2_size);

	for (int i = 0; i < num_child; i++)
	{
		if (i == num_child - 1) delta += (fsize1 % num_child);
		p_ids[i] = fork();
		if (p_ids[i] == 0) // Child node
		{
			int fd1 = open(pathname1, O_RDONLY);
			int fd2 = open(pathname2, O_RDONLY);
			// moving to start
			lseek(fd1, start, SEEK_SET);
			lseek(fd2, start, SEEK_SET);
			void* buf1 = malloc(delta);
			void* buf2 = malloc(delta);
			read(fd1, buf1, delta);
			read(fd2, buf2, delta);
			close(fd1);
			close(fd2);
			int res = memcmp(buf1, buf2, delta);
			// printf("child con pid: %d, diff: %d\nstart at %ld for %ld as delta\nbuf1: %p\n", getpid(), res, start, delta, buf1);
			free(buf1);
			free(buf2);
			if (res == 0) // Nessuna differenza, sono uguali
				exit(0);
			else
				exit(1);
		}
		start += delta;
	}
	int wstatus;
	while (wait(&wstatus) > 0)
	{
		if (WEXITSTATUS(wstatus) == 1) // se e' terminato con exit(1)
		{
			for (int i = 0; i < num_child; i++) kill(p_ids[i], SIGKILL);
			printf("%s %s differ\n", pathname1, pathname2);
			exit(EXIT_SUCCESS);
		}
	}
	close(fd1);
	close(fd2);
	exit(EXIT_SUCCESS);
}
