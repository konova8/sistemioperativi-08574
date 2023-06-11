#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h> 
#include <sys/wait.h>
#include <pthread.h>
#include <errno.h>  
#include <string.h>

#define MAXOPTIONS 10

int main(int argc, char* argv[]){
    int num_of_commands = 0;
    const int MAXCOM = atoi(argv[1]);
    char *command[MAXOPTIONS];
    for(int i = 2; i < argc; i++){
        int j = 0;
        while(i<argc && strcmp(argv[i], "//")!=0){
            command[j++] = argv[i++];
        }
        command[j] = NULL;
        num_of_commands++;
        pid_t pid = fork();
        if(pid == 0){
            execvp(command[0], command);
        }
        if(num_of_commands == MAXCOM){
            int status;
            wait(&status);
            num_of_commands--;
        }
    }
    for (int i = 0; i < num_of_commands; i++)
    {
        int status;
        wait(&status);
    }
    return 0;
}