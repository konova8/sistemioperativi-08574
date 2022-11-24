#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>

int main() {
	uid_t ruid,euid,suid;
	gid_t rgid,egid,sgid;
	getresuid(&ruid, &euid, &suid);
	getresgid(&rgid, &egid, &sgid);

	printf("uid %d %d %d\n", ruid,euid,suid);
	printf("gid %d %d %d\n", rgid,egid,sgid);
}
