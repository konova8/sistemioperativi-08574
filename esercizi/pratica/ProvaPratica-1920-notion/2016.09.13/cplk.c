#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>
#include <string.h>
#include <grp.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/queue.h>
#include <sys/prctl.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/eventfd.h>
#include <stdbool.h>
#include <sys/inotify.h>
#include <sys/signalfd.h>
#include <sys/sendfile.h>

int main(int argc, char *argv[]){
	int fd1, fd2;
	fd2 = open(argv[2], O_WRONLY);
	if(fcntl(fd2, F_WRLCK) == -1){
		perror("ERRORE");
		exit(EXIT_FAILURE);
	}
	struct stat st; 
    	stat(argv[1], &st);
	printf("locked\n");	
	fd1 = open(argv[1], O_RDONLY);
	srand(time(NULL));	
	sleep(rand()%10 +1);
	ssize_t res;
	res = sendfile(fd2, fd1, 0, st.st_size);
	if(fcntl(fd2, F_UNLCK) == -1){
		perror("ERRORE");
		exit(EXIT_FAILURE);
	}
	printf("unblocked\n");
    sleep(rand()%10 +1);
	close(fd1);
	close(fd2);
}
