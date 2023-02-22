#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
typedef struct timeval t_time;

int diff(t_time old, t_time new)
{
	long long	oldms;
	long long	newms;
	int			ret;

	oldms = old.tv_sec * 1000 + old.tv_usec / 1000;
	newms = new.tv_sec * 1000 + new.tv_usec / 1000;
	ret = newms - oldms;
	return (ret);
}

int	get_rest_time(t_time start_time)
{
	t_time	cur;
	int		passed;

	gettimeofday(&cur, NULL);
	passed = diff(start_time, cur);
	return (310 - passed);
}

int	main()
{
	t_time start_time;
	t_time old;
	t_time new;

	gettimeofday(&start_time, NULL);
	usleep(10000);
	gettimeofday(&old, NULL);
	usleep(10000);
	gettimeofday(&new, NULL);
	printf("diff: %d\n", diff(old, new));
	printf("passed : %d\n", get_rest_time(start_time));
}
