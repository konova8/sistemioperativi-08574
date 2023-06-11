#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h> 
#include <sys/wait.h>
#include <pthread.h>
#include <errno.h>  
#include <string.h>
#include <sys/prctl.h>
#include <sys/syscall.h>

int main(int argc, char *argv[]){
    prctl(PR_SET_CHILD_SUBREAPER, 1, 0, 0, 0, 0);
    if(fork() == 0){
        if(fork()!=0){
            printf("First child ends, pid: %d, parent: %d\n", getpid(), getppid());
            exit(0);
        }
        else{
            printf("Granchild starts, pid: %d, parent: %d\n", getpid(), getppid());
            sleep(2);
            printf("Granchild ends, pid: %d, parent: %d\n", getpid(), getppid());
            exit(0);
        }
    }
    else{
        for (int i = 0; i < 2; i++)
        {
            int status;
            pid_t pid = wait(&status);

            printf("wait for pid: %d\n", pid);
        }
    }
    return 0;
}