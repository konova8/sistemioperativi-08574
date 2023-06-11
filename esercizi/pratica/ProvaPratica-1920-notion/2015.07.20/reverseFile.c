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

unsigned char reverse(unsigned char b) {
   b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
   b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
   b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
   return b;
}

int main(int argc, char const *argv[]){
    if(argc < 2){
        perror("ERRORE");
        exit(EXIT_FAILURE);
    }
    const char *filename = argv[1];
    char c;
    FILE *fr = fopen(filename,"rb");
    FILE *fw = fopen(filename,"ab");
    if(fr == NULL || fw == NULL){
        perror("ERRORE");
        fclose(fr);
        fclose(fw);
        exit(EXIT_FAILURE);
    }
    struct stat file;
    stat(filename, &file);
    printf("LEN %ld\n", file.st_size);
    for(int i=0; i<file.st_size; i++){
        fread(&c, sizeof(char),1,fr);
        char rev = reverse(c);
        fwrite(&rev, sizeof(char),1,fw);
    }
    fclose(fr);
    fclose(fw);
    return 0;
}
