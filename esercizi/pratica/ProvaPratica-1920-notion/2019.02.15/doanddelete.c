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

#define EVENT_BUF_LEN 4096

char directory[PATH_MAX];

int dirExists (const char *d){
    int flags = O_DIRECTORY | O_RDONLY;
    int mode = S_IRUSR | S_IWUSR;
    int fd = open (d, flags, mode);

    if (fd < 0)     /* directory does not exist */
        return 0;
    else if (fd) {  /* directory exists, rtn fd */
        close (fd);
    }

    return fd;
}


int isEmpty(const char *path) {
    DIR *dir = opendir(path);
    struct dirent *entry;
    int fileCount = 0;
    while((entry = readdir(dir)) != NULL) {
        if(entry->d_type == DT_DIR) {
            if(strcmp(entry->d_name, "..") == 0 || strcmp(entry->d_name, ".") == 0) {
                continue;
            }
        }
        fileCount++;
    }
    closedir(dir);
    return (fileCount == 0);
}

int execFile(char *filename, const char* cartella) {
    char toExec[1000];
    chdir(cartella);

    char* arg[] = {filename, NULL};
    int err = execv(filename, arg);
    if(err == -1) {
        printf("Error: %s\n", strerror(errno));
        return -1;
    }
    return 0;
}

int main(int argc, char const *argv[]){
    
    if(argc != 2){
        printf("Input error\n");
        return 1;
    }
    
    const char *path = argv[1]; 
    if(!dirExists(path)){
        printf("Directory not found\n");
        return 2;
    }

    if(!isEmpty(path)){
        printf("Directory not empty\n");
        return 3;
    }
    
    char currentDir[1000];
    char currentPath[1000];
    realpath(getcwd(currentDir,1000), currentPath);

    int len=0;
    int fd, wd;
    char buffer[EVENT_BUF_LEN];
    struct inotify_event *event;

    fd = inotify_init();
    wd = inotify_add_watch(fd, path, IN_CREATE);

    while(1){
        len = read(fd, buffer, EVENT_BUF_LEN);
        pid_t pid; 
        for (char *ptr = buffer; ptr < buffer + len; ptr += sizeof(struct inotify_event) + event->len) {
            event = (struct inotify_event *) ptr;
            //Print the name of the file
            if (event->len){
                if(event->mask & IN_CREATE){
                    //Eseguire il file
                    if((pid = fork()) == 0){
                        execFile(event->name, argv[1]);
                        kill(getpid(), SIGKILL);
                    }
                    else{
                        int status;
                        waitpid(pid, &status, 0);
                        char toRemove[1000];
                        memset(toRemove, 0, 1000);
                        strcat(toRemove, argv[1]);
                        strcat(toRemove, "/");
                        strcat(toRemove, event->name);
                        remove(toRemove);
                    }                    
                }
            }
        }       
    }
    inotify_rm_watch (fd, wd);  
    close (fd);
    return 0;
}
