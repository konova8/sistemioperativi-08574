#include <sys/inotify.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/signalfd.h>


int main(int argc, char *argv[]){
    FILE *tmp = fopen("./tmp/countpid","w");
    fprintf(tmp,"%d\n",getpid());
    fclose(tmp);
    int sfd;
    int count = 0;
	sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    sigaddset(&mask, SIGUSR2);
    if (sigprocmask(SIG_BLOCK, &mask, NULL) < 0) {
		perror ("sigprocmask");
		return 1;
	}
    sfd = signalfd (-1, &mask, 0);
    if (sfd < 0) {
		perror ("signalfd");
		return 1;
	}
    while(1){
        struct signalfd_siginfo si;
        ssize_t res = read (sfd, &si, sizeof(si));
        if (res < 0) {
            perror ("read");
			return 1;
        }
        if (res != sizeof(si)) {
			fprintf (stderr, "Something wrong\n");
			return 1;
		}
        if(si.ssi_signo == SIGUSR1){
            printf("SIGUSR1. New value: %d\n",++count);
        }
        else if(si.ssi_signo == SIGUSR2){
            printf("SIGUSR2. New value: %d\n",--count);
        }
        else {
			fprintf (stderr, "Got some unhandled signal\n");
			return 1;
		}
    }
    close(sfd);
    return 0;
}