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


typedef struct inode_list {
    ino_t inode;
    struct inode_list* next;
}inode_list;

int n_file = 0, n_dir = 0;
inode_list *head = NULL;

bool is_inode_in_list(int inode){
    inode_list *tmp = head;
    while(tmp != NULL){
        if(tmp->inode == inode)
            return true;
        tmp = tmp->next; 
    }
    return false;
}

void add_inode_to_list(int inode){
    inode_list *tmp = malloc(sizeof(inode_list));
    tmp->inode = inode;
    tmp->next = head;
    head = tmp;
}   



void count(char *path){
    DIR *dir;
    dir = opendir(path);
    struct dirent *entry;   
    while (entry = readdir(dir), entry != NULL) {
        if(strcmp(entry->d_name,".") == 0 || strcmp(entry->d_name,"..") == 0){
            continue;
        }
        if(!is_inode_in_list(entry->d_ino)){
            add_inode_to_list(entry->d_ino);
            if (entry->d_type == DT_DIR) {
                n_dir += 1;
                char *newPath = malloc(sizeof(char[256]));                
                strcpy(newPath, path);
                strcat(newPath, "/");
                strcat(newPath, entry->d_name);
                count(newPath);
                free(newPath);
            } else if(entry->d_type == DT_REG){
                n_file += 1;
            }   
        }
    }
}

int main(int argc, char const *argv[]){
    char *path = malloc(sizeof(char[256]));
    if(argc == 1){
        strcpy(path,".");
    }
    else{
        strcpy(path, argv[1]);    
    }
    count(path);
    printf("File: %d  , Dir %d\n",n_file, n_dir);
    free(path);
    return 0;
}
