#include "../philo_bonus_/philo_bonus.h"

void function(sem_t *sem, int i)
{
	sem_wait(sem);
	printf("[%d] locked sem\n", i);
	sleep(3);
	sem_post(sem);
	printf("[%d] unlocked sem\n", i);
	exit(0);
}

int main()
{
	pid_t	pid[3];
	int		status;
	sem_t	*sem;

	sem = sem_open("sem", O_CREAT, S_IRWXU, 2);
	for (int i = 1; i <= 2; i++)
		sem_post(sem);

	for (int i = 1; i <= 3; i++)
	{
		pid[i] = fork();
		if (pid[i] == 0)
		{
			function(sem, i);
		}
	}
	
	waitpid(-1, &status, 0);
	printf("------------@-------------\n");
	// kill(pid[0], SIGKILL);
	for (int i = 1; i <= 3; i++)
	{
		if (kill(pid[i], SIGKILL) == 0)
			printf("kill child [%d]\n", i);
	}
	printf("fin\n");
}
// 왜 semaphore 2개 만들고 2개 언록했는데 출력이 다른지@@@@!@@@#@$@#


ㅓㄴㅇ리ㅓㅁㄴ;ㅣㅓ림너리ㅑㅁ너ㅣㄹ


