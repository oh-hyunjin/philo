#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

int	main()
{
	struct timeval	time;

	for (int i = 0; i < 10; i++)
	{
		gettimeofday(&time, NULL);
		printf("%ld, %dus = %dms\n", time.tv_sec, time.tv_usec, time.tv_usec / 1000);
		usleep(1000);
	}
}
