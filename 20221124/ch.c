#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {
	char *old = getcwd(NULL, 0);
	chdir(argv[1]);
	char *new = getcwd(NULL, 0);
	printf("%s\n", new);
	chdir(old);
	char *actual = getcwd(NULL, 0);
	printf("%s\n", actual);
	free(old);
	free(new);
	free(actual);
}
