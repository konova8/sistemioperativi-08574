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

#define EVENT_BUF_LEN 1024

bool isNumeric(char name[]){
    int len = strlen(name);
    int i =0;
    while(i<len && name[i]!='\0'){
        if(name[i]<'0' || name[i]>='9') return false;
        i++;
    }
    return true;
}

int main(int argc, char const *argv[]){
    int fd;
    int numProc=0, oldProc = 0;
    fd = inotify_init();
    DIR *dir = opendir("/proc");
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL){
        if(entry->d_type == DT_DIR && isNumeric(entry->d_name)){
            numProc++;
        }
    }
    printf("Iniziale: %d\n",numProc);
    closedir(dir);
    struct inotify_event *event;
    if(inotify_add_watch(fd,"/proc",IN_CREATE || IN_DELETE) == -1){
        perror("inotify_add_watch");
        return 1;
    }
    char buffer[EVENT_BUF_LEN];
    while(1){
        int len = read(fd, buffer, EVENT_BUF_LEN);
        for(char *ptr = buffer; ptr < buffer + len; ptr+=sizeof(struct inotify_event) + event->len){
            event = (struct inotify_event *) ptr;
            if(event->mask & IN_CREATE){
                if(isNumeric(event->name)){
                    numProc++;
                    printf("Nuovo numero %d\n",numProc);
                }
            }
            else if(event->mask & IN_DELETE){
                if(isNumeric(event->name)){
                    numProc--;
                    printf("%d\n",numProc);
                }
            }
        }
    }

    return 0;
}
