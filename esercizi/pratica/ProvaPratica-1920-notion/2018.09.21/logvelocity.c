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
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/signalfd.h>

#define MAXFILE 10000

int main(int argc, char *argv[]){
    FILE *log = fopen(argv[1], "r");
    char *line=NULL;
    size_t len = 0;
    ssize_t read;
    bool first = true;
    int oldtime, newtime;

    while((read = getline(&line, &len, log))!=-1){
        char hour[3];
        hour[0] = line[7];
        hour[1] = line[8];
        hour[2] = '\0';

        char min[3];
        min[0] = line[10];
        min[1] = line[11];
        min[2] = '\0';

        char sec[3];
        sec[0] = line[13];
        sec[1] = line[14];
        sec[2] = '\0';
        if(first){
            printf("%s",line);
            first = false;
            oldtime = atoi(hour)*60*60 + atoi(min)*60 + atoi(sec);
        }
        else{
            newtime = atoi(hour)*60*60 + atoi(min)*60 + atoi(sec);
            sleep(newtime - oldtime);
            printf("%s",line);
            oldtime = newtime;
        }
    }
    printf("\n");
    return 0;
}