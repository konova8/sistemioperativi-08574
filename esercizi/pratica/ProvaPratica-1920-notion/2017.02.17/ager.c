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
#include <sys/inotify.h>
#include <sys/signalfd.h>

int main(int argc, char *argv[]){
    if(argc < 2){
        exit(EXIT_FAILURE);
    }
    char *path = argv[1];
    struct stat info;
    int fd;
    if((fd = open(path, O_WRONLY)) == -1){
        exit(EXIT_FAILURE);
    }
    if(fstat(fd,&info) == -1){
        exit(EXIT_FAILURE);
    }
    struct timeval times[2];
    times[0].tv_sec = info.st_atim.tv_sec - (10 * 86400);
    times[1].tv_sec = info.st_atim.tv_sec - (10 * 86400);
    if (utimes(path, times) == -1)
    {
        perror("utime error: ");
    }
    close(fd);
}