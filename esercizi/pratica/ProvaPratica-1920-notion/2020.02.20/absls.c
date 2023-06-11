#include <stdio.h>
#include <unistd.h> 
#include <dirent.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>  


int main(int argc, char *argv[]){
    DIR *directory;
    struct dirent *entry;
    char buff_abs[PATH_MAX];
    char *abs_path;
    
    if (chdir(argv[1]) == -1){
        perror("chdir error: ");
    }
    
    if((directory = opendir(argv[1])) == NULL){
        perror("opendir error: ");
    }

    while((entry = readdir(directory)) != NULL){
        if((abs_path = realpath(entry->d_name, buff_abs)) == NULL){
            perror("realpath error: ");
        }
        printf("Entry %s abs path is %s \n",entry->d_name, abs_path);
    }

    close(directory);
}