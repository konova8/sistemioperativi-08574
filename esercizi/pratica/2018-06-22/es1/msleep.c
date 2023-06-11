#include <bits/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/timerfd.h>
#include <unistd.h>
#include <stdint.h>

typedef int fd_t;

int main(int argv, char* argc[])
{
	if (argv != 2)
		exit(1);

	double ms_to_sleep = atof(argc[1]);

	//sleep(ms_to_sleep / 1000);
	fd_t clock_fd = timerfd_create(CLOCK_REALTIME, 0);

	uint64_t exp;
	while(read(clock_fd, &exp, sizeof(uint64_t)) < 0) // wait for timer to expire
	{
		if (exp == clock_gettime(CLOCK_REALTIME, ))
		printf("busy waiting\n");
	}
	printf("finito\n");

	return 0;
}
