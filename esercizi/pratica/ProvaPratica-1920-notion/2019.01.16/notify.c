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


#define EVENT_BUF_LEN 1024

int main(int argc, char *argv[]) {
    if(argc == 1){
        perror("No parameters");
        return 1;
    }
    int fd = inotify_init();
    char *path = argv[1]; 
    int wd = inotify_add_watch(fd, path, IN_DELETE);
    struct inotify_event *event;
    char buffer[EVENT_BUF_LEN];
    while(1){
        int len = read(fd, buffer, EVENT_BUF_LEN);
        for(char *ptr = buffer; ptr < buffer + len; ptr+=sizeof(struct inotify_event) + event->len){
            event = (struct inotify_event *) ptr;
            if(event->len){
                if(event->mask & IN_DELETE){    
                    char *pathdel;
                    strcpy(pathdel, "");
                    strcat(pathdel,argv[1]);
                    strcat(pathdel,"/");
                    strcat(pathdel,event->name);
                    FILE *fp = fopen(pathdel, "w");
                    fclose(fp);
                }
            }
        }
    }
}