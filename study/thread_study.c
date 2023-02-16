#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

typedef struct s_info
{
	int	num;
	int	*share;
} t_info;

void	init(t_info **info, int *share)
{
	*info = (t_info *)malloc(sizeof(t_info) * 3);

	for (int i = 0; i < 3; i ++)
	{
		(*info)[i].num = i;
		(*info)[i].share = share;
	}

	printf("---in init---\n");
	for (int i = 0; i < 3; i ++)
		printf("%d: %d, %d\n", i, (*info)[i].num, *(*info)[i].share);
	printf("\n");
}

void	routine(void *param)
{
	t_info	*info;
	info = (t_info *)param;

	printf("---in routine---\n");
	printf("num: %d, share: %d\n", info->num, *info->share);
	printf("\n");
}

int main()
{
	t_info	*info; // array 3
	int		share;

	init(&info, &share);

	printf("---in main---\n");
	for (int i = 0; i < 3; i ++)
		printf("%d: %d, %d\n", i, info[i].num, *info[i].share);
	printf("\n");

	share = 0;

	for (int i = 0; i < 3; i++)
		routine(&info[i]);
}
