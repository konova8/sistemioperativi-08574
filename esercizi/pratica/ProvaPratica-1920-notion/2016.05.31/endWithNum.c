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

typedef struct list_of_file{
    char filename[256];
    int num;
    struct list_of_file *next;
}list_of_file;

list_of_file *insertOrder(list_of_file *head, char filename[], int num){
    if(head == NULL){
        list_of_file *tmp = malloc(sizeof(list_of_file));
        strcpy(tmp->filename, filename);
        tmp->num = num;
        tmp->next = NULL;
        return tmp;
    }
    else{
        if(head->num < num){
            head->next = insertOrder(head->next, filename, num);
            return head;
        }
        else{
            list_of_file *tmp = malloc(sizeof(list_of_file));
            strcpy(tmp->filename, filename);
            tmp->num = num;
            tmp->next = head;
            return tmp;
        }
    }
}

int main(int argc, char const *argv[])
{
    list_of_file *head = NULL;
    const char *path = argv[1];
    DIR *dir = opendir(path);
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL){
        if(entry->d_type != DT_DIR){
            char *nameFile = entry->d_name;
            char *point = strrchr(nameFile, '.');
            if(point != NULL){
                char *number = malloc(sizeof(char[256])); 
                number = strcpy(number, point);
                number++;
                char *tmp;
                int num = strtol(number, &tmp, 10);
                if(tmp != number){
                    head = insertOrder(head, entry->d_name, num);
                }
            }
        }
    }
    while(head != NULL){
        printf("%s\n",head->filename);
        head=head->next;
    }
    return 0;
}
