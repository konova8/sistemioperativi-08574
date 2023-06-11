#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h> 
#include <sys/wait.h>
#include <pthread.h>
#include <errno.h>  
#include <string.h>

#define MAXOPTIONS 10

int main(int argc, char *argv[]){
    char *command[MAXOPTIONS];
    int num_cmd = 0;
    for(int i=1; i<argc; i++){
        int j = 0;
        while(i<argc && strcmp(argv[i], "//") != 0){
            command[j++] = argv[i++];
        }
        command[j] = NULL;
        num_cmd++;
        pid_t pid = fork();
        if(pid == 0){
            execvp(command[0], command);
            exit(1);
        }
    }
    for(int i=1; i<num_cmd; i++){
        int status;
        wait(&status);
    }
    return 0;
}