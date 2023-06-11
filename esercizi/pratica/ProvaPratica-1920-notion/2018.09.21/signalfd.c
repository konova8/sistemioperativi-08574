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
    int sfd;
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    sigaddset(&mask, SIGUSR2);
    sfd = signalfd(-1, &mask, 0);
    if(sfd < 0){
        perror("signalfd");
        return 1;
    }
    while(1){
        struct signalfd_siginfo si;
        ssize_t res = read(sfd, &si, sizeof(struct signalfd_siginfo));
        if(res < 0){
            perror("read");
            return 1;
        }
        if (res != sizeof(si)) {
			fprintf (stderr, "Something wrong\n");
			return 1;
		}
        if(si.ssi_signo == SIGUSR1){
            char filename[1000];
            char *pidname = (char *)si.ssi_pid;
            strcpy(filename,"");
            strcat(filename, pidname);
            FILE *f = open(si.ssi_pid, "a");
            fprintf(f, "USR1 %s\n",ctime(time(si.ssi_stime)));
            fclose(f);
        }
        else if(si.ssi_signo == SIGUSR2){
            char filename[1000];
            char *pidname = (char *)si.ssi_pid;
            strcpy(filename,"");
            strcat(filename, pidname);
            FILE *f = open(si.ssi_pid, "a");
            fprintf(f, "USR2 %s\n",ctime(time(si.ssi_stime)));
            fclose(f);
        }
    }
    close(sfd);
}   