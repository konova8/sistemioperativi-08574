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
#include <poll.h>

int comp (const void * elem1, const void * elem2) 
{
    long f = *((long*)elem1);
    long s = *((long*)elem2);
    if (f > s) return  1;
    if (f < s) return -1;
    return 0;
}

int main(int argc, char *argv[]){
    if(argc < 2){
        perror("Missing parameters");
        exit(EXIT_FAILURE);
    }

    long milliseconds[argc-1];
    struct itimerspec new_value[argc-1];
    int timerfd[argc-1];
    struct pollfd ufds[argc-1];

    for(int i = 1; i < argc; i++){
        milliseconds[i-1] = atoi(argv[i]);
    }
    qsort(milliseconds, sizeof(milliseconds)/sizeof(*milliseconds),sizeof(*milliseconds), comp);
    for(int i = 0; i < argc-1; i++){
        new_value[i].it_interval.tv_nsec = new_value[i].it_interval.tv_sec = 0;
        new_value[i].it_value.tv_sec = milliseconds[i] / 1000;
        new_value[i].it_value.tv_nsec = milliseconds[i] * 1000;
        timerfd[i] = timerfd_create(CLOCK_REALTIME, 0);
        if (timerfd_settime(timerfd[i], 0, &new_value[i], NULL) == -1)
        {
            perror("error on settime: ");
            exit(EXIT_FAILURE);
        }
        ufds[i].fd = timerfd[i];
        ufds[i].events = POLLIN;
    }
    for (int i = 0; i < argc-1; i++){
        int fd = poll(ufds + i, argc-1, -1);
        printf("%lu\n", milliseconds[i]);
    }
    return 0;
}