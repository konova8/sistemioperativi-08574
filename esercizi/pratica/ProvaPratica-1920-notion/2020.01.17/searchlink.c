#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>


#define DIRMAX 10000

ino_t find_inode(char* file_name, char *dir_path)
{
    DIR *dir;
    struct dirent *entry;
    struct stat info;
    struct dirent *entries[DIRMAX];
    int i = 0;

    /*cambia current dir*/
    if (chdir(dir_path) == -1){
        perror("error chdir: ");
    }

    /*apre la current dir*/
    if ((dir = opendir(".")) == NULL){
        perror("error opendir: ");
    }

    while ((entry = readdir(dir)) != NULL){
        /*prende le informazioni del file*/
        if (stat(entry->d_name, &info) == -1){
            perror("error stat: ");
            continue;
        }

        /*se il file non e' una dir*/
        if (S_ISDIR(info.st_mode) == 0){
            /*vede se fa match con il nome*/
            if (strcmp(file_name, entry->d_name) == 0){
                return info.st_ino;
            }
        }

        /*altrimenti lo aggiunge alle dir incontrate in questa dir*/
        else if (S_ISDIR(info.st_mode) && (strcmp(entry->d_name, ".") != 0) && (strcmp(entry->d_name, "..") != 0)){
            entries[i] = entry;
            i++;
        }
    }

    /*se il file non era in questa scandisce le dir ricorsivamente finche' lo trova o meno*/
    for (int j = 0; j < i; j++){
        ino_t result;
        if((result = find_inode(file_name, entries[j]->d_name)) != -1){
            chdir("..");
            return result;
        }
        else{
            chdir("..");
        }

    }
    return -1;

}

void listdir(char *dir_path, ino_t inode, char *relpath){
    DIR *dir;
    struct dirent *entry;
    struct stat info;
    int stop = 0;

    if(chdir(dir_path) == -1){
        perror("Chdir error: ");
    }
    if((dir=opendir(".")) == -1){
        perror("opendir error: ");
    }
    while ((entry = readdir(dir)) != NULL && !stop){
        if (stat(entry->d_name, &info) == -1){
            perror("error stat: ");
            continue;
        }
        if(info.st_ino == inode){
            struct stat info2;
            lstat(entry->d_name, &info2);
            if(S_ISLNK(info2.st_mode)){
                char src[PATH_MAX];
                char dest[PATH_MAX];
                strcpy(dest, relpath);
                strcpy(src, "/");
                strcpy(dest, relpath);
                strcat(dest, src);
                strcpy(src, entry->d_name);
                strcat(dest, src);
                printf("Sym link %s\n", dest);
            }
            else{
                char src[PATH_MAX];
                char dest[PATH_MAX];
                strcpy(dest, relpath);
                strcpy(src, "/");
                strcpy(dest, relpath);
                strcat(dest, src);
                strcpy(src, entry->d_name);
                strcat(dest, src);
                printf("Hard link %s\n", dest);
            }
        }
        else if(S_ISDIR(info.st_mode) && (strcmp(entry->d_name, ".") != 0) && (strcmp(entry->d_name, "..") != 0)){
            pid_t pid = fork();
            switch (pid){
            case 0:
                ;
                char src[PATH_MAX];
                char dest[PATH_MAX];
                strcpy(dest, relpath);
                strcpy(src, "/");
                strcat(dest, src);
                strcpy(src, entry->d_name);
                strcat(dest, src);
                listdir(entry->d_name, inode, dest);
                stop = 1;
                break;
            default:
                ;
                int status;
                waitpid(pid, &status, 0);
                break;
            }
        }
    }
}

int main(int argc, char *argv[]){
    ino_t inode = find_inode(argv[1], argv[2]);
    if(inode == -1){
        exit(EXIT_FAILURE);
    }

    listdir("./", inode, ".");
    return 0;
}