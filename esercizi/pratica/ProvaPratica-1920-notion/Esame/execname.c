#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <string.h>
#include <unistd.h>
#include <malloc.h>
#include <sys/wait.h>

#define EVENT_SIZE  (sizeof(struct inotify_event))
#define BUF_LEN     (1024 * (EVENT_SIZE + 16))

void split(char src[], char *dest[]){
	char *token = strtok(src, " ");
	int i = 0;
	while (token != NULL){
		dest[i] = malloc(sizeof(char[100]));
        	strcpy(dest[i++],token);
        	token = strtok(NULL, " ");
    	}
	dest[i] = NULL;
}

int main(int argc, char *argv[]){
	int length, i = 0;
    	int fd;
    	int wd;
    	char buffer[BUF_LEN];
	fd = inotify_init();
	if (fd < 0) {
        	perror("inotify_init");
		exit(EXIT_FAILURE);
    	}

    	wd = inotify_add_watch(fd, "exec", IN_CREATE);
    	while(1){
		i = 0;
		length = read(fd, buffer, BUF_LEN);
		while(i<length){
			struct inotify_event *event = (struct inotify_event *) &buffer[i];	
			if(event->len){
				char *arg[10];
				if(event->mask & IN_CREATE){
					char name[255];
					strcpy(name,event->name);
					split(event->name, arg);
					if(fork()==0){
						execlp(arg[0], arg[0], arg[1], arg[2], arg[3], arg[4], arg[5], arg[6], arg[7], arg[8], arg[9], NULL);
					}
					else{
						int status;
						wait(&status);
						char *path = malloc(sizeof(char[255]));
						strcat(path,"exec/");
						strcat(path, name);
						remove(path);
					}
				}			
			}
			i += EVENT_SIZE + event->len;
		}
	}
}
