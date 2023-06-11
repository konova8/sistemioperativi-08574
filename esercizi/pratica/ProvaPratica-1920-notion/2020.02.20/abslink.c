#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <unistd.h> 
#include <stdlib.h>
#include <errno.h>  


int main(int argc, char *argv[]){
    char relative[PATH_MAX];
    char absolute[PATH_MAX];
    char new_link_name[PATH_MAX];
    char *ptr;

    if(readlink(argv[1],relative, PATH_MAX) == -1){
        perror("Error on readlink");
    }

    if((ptr = realpath(relative, absolute)) == NULL){
        perror("Error on realpath");
    }

    strncpy(new_link_name, argv[1], PATH_MAX);

    char *new_linkPtr = strcat(new_link_name, "_abs");

    unlink(new_linkPtr);

    if(symlink(ptr, new_linkPtr) == -1){
        perror("Error on symlink");
    }
    return 0;
}