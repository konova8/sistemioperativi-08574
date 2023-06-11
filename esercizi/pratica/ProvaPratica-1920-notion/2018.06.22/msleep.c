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
#include <sys/timerfd.h>

int main(int argc, char *argv[]){
    if(argc < 2){
        perror("Missing parameters");
        return 2;
    }
    int ms = atoi(argv[1]);
    struct itimerspec ts;
    ts.it_interval.tv_nsec = 0;
    ts.it_interval.tv_nsec = 0;
    ts.it_value.tv_sec = ms / 1000;
    ts.it_value.tv_nsec = ms * 1000;

    int tfd = timerfd_create(CLOCK_REALTIME, 0);
    uint64_t expiration;
    if(timerfd_settime(tfd, 0, &ts, NULL) == -1){
        perror("timerfd_settime");
        exit(EXIT_FAILURE);
    }
    uint64_t expirations;
    expirations = read(tfd, &expirations, sizeof(uint64_t));
    return 0;
}