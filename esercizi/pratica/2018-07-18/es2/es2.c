#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define FILE_NAME "/tmp/countpid"
int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: %s <things-to-exec>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  // Leggo pid in /tmp/countpid
  FILE *file_ptr = fopen(FILE_NAME, "r");
  int pid_es1;
  fscanf(file_ptr, "%d", &pid_es1);
  fclose(file_ptr);

  kill(pid_es1, SIGUSR1);

  if (fork() == 0) {
    execvp(argv[1], &argv[1]);
  } else {
    wait(NULL);
    kill(pid_es1, SIGUSR2);
  }

  exit(EXIT_SUCCESS);
}
