#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define DELIM "//"

void parseArgs(char *source, char **destination) {
  char *tmp;
  int i = 0;
  tmp = strtok(source, " ");
  do {
    printf("parseArgs: %s\n", tmp);
    destination[i] = tmp;
    i++;
  } while ((tmp = strtok(NULL, "//")) != NULL);
}

int main(int argc, char *argv[]) {
  int sum = 0;
  for (int i = 1; i < argc; i++)
    sum += strlen(argv[i]) + 1;
  char *to_parse = malloc(sum * sizeof(char));
  for (int i = 1; i < argc; i++) {
    printf("%s\n", argv[i]);
    strcat(to_parse, argv[i]);
    if (i != argc - 1)
      strcat(to_parse, " ");
    printf("%s\n", to_parse);
  }
  // printf("to_parse = %s|\n", to_parse);
  char *tmp;
  tmp = strtok(to_parse, "//");
  do {
    printf("Will do %s:\n", tmp);
    pid_t pid_child = fork();
    if (pid_child == 0) {
      printf("Dentro al figlio con %s\n", tmp);
      // arr = [ls, -l, NULL]
      char *arr[500];
      parseArgs(tmp, arr);
      printf("%s %s", arr[0], arr[1]);
      execvp(arr[0], arr);
    }
  } while ((tmp = strtok(NULL, "//")) != NULL);

  return 0;
}
