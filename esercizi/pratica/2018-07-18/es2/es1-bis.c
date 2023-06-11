#include <sys/signalfd.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define FILE_NAME "/tmp/countpid"
#define handle_error(msg) \
	do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main(int argc, char *argv[])
{
    sigset_t mask;
    int sfd;
    struct signalfd_siginfo fdsi;
    ssize_t s;
    int pid_es1 = getpid();

    // Scrivo pid in /tmp/countpid
    FILE* file_ptr = fopen(FILE_NAME, "w");
    fprintf(file_ptr, "%d", pid_es1);
    fclose(file_ptr);

    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    sigaddset(&mask, SIGQUIT);
    sigaddset(&mask, SIGUSR1);
    sigaddset(&mask, SIGUSR2);

    /* Block signals so that they aren't handled
       according to their default dispositions. */

    if (sigprocmask(SIG_BLOCK, &mask, NULL) == -1)
        handle_error("sigprocmask");

    sfd = signalfd(-1, &mask, 0);
    if (sfd == -1)
        handle_error("signalfd");
	
    int count = 0;

    for (;;) {
        s = read(sfd, &fdsi, sizeof(fdsi));
        if (s != sizeof(fdsi))
            handle_error("read");

        if (fdsi.ssi_signo == SIGINT) {
            printf("Got SIGINT\n");
            exit(EXIT_FAILURE);
        } else if (fdsi.ssi_signo == SIGQUIT) {
            printf("Got SIGQUIT\n");
            exit(EXIT_SUCCESS);
	} else if (fdsi.ssi_signo == SIGUSR1) {
	    count++;
	    printf("count = %d\n", count);
	} else if (fdsi.ssi_signo == SIGUSR2) {
	    count--;
	    printf("count = %d\n", count);
        } else {
            printf("Read unexpected signal\n");
        }
    }
}
