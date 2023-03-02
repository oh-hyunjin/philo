#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
typedef struct timeval t_time;

int main()
{
	sem_t test;
	test = sem_open("test", O_CREAT, S_IRWXU, 3); // o_flags?????????
	printf("sem num : %d\n", (int*)test);
}