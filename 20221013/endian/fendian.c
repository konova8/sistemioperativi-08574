#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
	FILE *f;
	int val;
	switch (argc) {
		case 2:
			f = fopen(argv[1], "r");
			fread(&val, 1, sizeof(val), f);
			printf("%d %x\n",val,val);
			fclose(f);
			break;
		case 3:
			val = strtol(argv[1], NULL, 0);
			f = fopen(argv[2], "w");
			fwrite(&val, 1, sizeof(val), f);
			fclose(f);
			break;
		default:
			printf("ERR\n");
			return 1;
	}
	return 0;
}


