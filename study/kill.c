#include "../philo_bonus_/philo_bonus.h"
#include <errno.h>
#include <string.h>

void *check_thread(void *param)
{
	int	*a;

	a = (int *)param;
	printf("[%d] is in check thread\n", *a);
	sleep(3);
	printf("[%d] check thread exit\n", *a);
	exit(0);
	return (0);
}

void function(sem_t *sem, int i)
{
	pthread_t thr;

	printf("[%d] <%d> is in function\n", i, getpid());
	pthread_create(&thr, NULL, check_thread, &i);
	while (1)
	{
		sem_wait(sem);
		printf("[%d] locked sem\n", i); // lock
		sleep(200);
		sem_post(sem);
		printf("[%d] unlocked sem\n", i); // unlock
	}
	printf("thread detach res: %d\n", pthread_detach(thr));
	exit(0);
}

void	*main_thread(void *param)
{
	printf("main thread start\n");
	(void)param;
	sleep(100);
	return (0);
}

int main()
{
	pid_t	pid[4];
	int		status;
	sem_t	*sem;

	sem_unlink("sem");
	sem = sem_open("sem", O_CREAT, 0644, 1);
	if (sem != SEM_FAILED)
		printf("psem open clear\n");
	printf("--------------------------\n");

	for (int i = 1; i <= 3; i++)
	{
		pid[i] = fork();
		if (pid[i] == 0)
			function(sem, i);
		else if (pid[i] < 0)
			printf("fork fail\n");
		sleep(1);
	}
	
	pthread_t main_thr;
	pthread_create(&main_thr, NULL, main_thread, NULL);

	waitpid(-1, &status, 0);
	printf("------------@-------------\n");
	// kill(pid[0], SIGKILL);
	for (int i = 1; i <= 3; i++)
	{
		printf("<%d> ", pid[i]);
		int kill_ret = kill(pid[i], SIGKILL);
		if (kill_ret == 0)
			printf("kill child [%d]\n", i);
		else if (kill_ret == -1)
			printf("%s\n", strerror(errno));
	}
	printf("sem close res : %d\n", sem_close(sem));
	printf("sem unlink res : %d\n", sem_unlink("sem"));
	printf("fin\n");
}

