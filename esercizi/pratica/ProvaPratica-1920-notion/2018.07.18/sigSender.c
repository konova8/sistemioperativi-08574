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
    int fd = open("./tmp/countpid", O_RDONLY);
    char pid[100];
    read(fd, pid, 100);
    kill(atoi(pid),SIGUSR1);
    if(fork() == 0){
        execvp(argv[1], argv + 1);
    }
    else{
        int status;
        wait(&status);
        kill(atoi(pid),SIGUSR2);
    }
    return 0;
}