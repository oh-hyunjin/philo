#include "../philo_bonus/philo_bonus.h"

void *thread(void *param)
{
	sem_t *sema;

	sema = (sem_t *)param;
	sem_wait(sema);
	printf("dont put this\n");
	return (0);
}

int main()
{
	sem_t *sema;
	pthread_t thread_id;

	sem_unlink("sema");
	sema = sem_open("full", O_CREAT, 0644, 0);
	pthread_create(&thread_id, NULL, thread, sema);

	sleep(2);
	printf("thread detach result : %d\n", pthread_detach(thread_id));
	printf("thread join result : %d : %s\n", pthread_join(thread_id, NULL), strerror(errno));
	printf("will close and unlink sema\n");

	printf("sem close result : %d\n", sem_close(sema));
	printf("sem unlink reslut : %d\n", sem_unlink("sema"));
}
