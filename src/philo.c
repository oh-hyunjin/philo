/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 11:17:50 by hyoh              #+#    #+#             */
/*   Updated: 2023/02/21 11:27:17 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	getting_fork(t_philo *philo, t_info *info, int *fst, int *snd)
{
	*fst = philo->id;
	*snd = philo->id + 1;
	if (philo->id == info->argu[NUMBER_OF_PHILOS]) // 총 한명일 때, 마지막 num일 때
		*snd = 1;
	printf("%d [%d] is waiting fork (<%d>:%d, <%d>:%d)\n", cur_time(philo), philo->id, \
						*fst, info->fork[*fst].status, *snd, info->fork[*snd].status);
	while (1)
	{ // freeze 되기 전에 lock or unlock 판별
		if (*fst != *snd && info->fork[*fst].status == UNLOCK \
				&& info->fork[*snd].status == UNLOCK)
		{
			info->fork[*fst].status++;
			info->fork[*snd].status++;
			print_action(READY_FORK, philo);
			break ;
		}
		if(get_rest_time(philo) < 0) //=은 안붙이나?
		{
			print_action(DYING, philo);
			printf("	was waiting for forks (<%d>:%d, <%d>:%d)\n", \
						*fst, info->fork[*fst].status, *snd, info->fork[*snd].status);
			info->share_status = DEAD;
			return (-1);
		}
	}
	if (info->fork[*fst].status >= 2)
		printf("fork [%d]trouble!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n", *fst);
	if (info->fork[*snd].status >= 2)
		printf("fork [%d]trouble!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n", *snd);
	if(pthread_mutex_lock(&info->fork[*fst].mutex) != 0)
		printf("mutex error!!!!!!!!!!!!!!!!! fork : %d\n", *fst);
	if (pthread_mutex_lock(&info->fork[*snd].mutex) != 0)
		printf("mutex error!!!!!!!!!!!!!!!!! fork : %d\n", *snd);
	print_action(TAKING_FORK, philo);
	return (0);
}

void	eating(t_philo *philo, t_info *info)
{
	int	fst;
	int	snd;

	if (info->share_status == DEAD)
		return ;
	if (getting_fork(philo, info, &fst, &snd) == -1)
		return ;

	// start eating
	philo->rest_num--;
	gettimeofday(&philo->time, NULL);
	print_action(EATING, philo);
	if (philo->rest_num == 0)
		printf("  %d satisfied must eat num~~~~~~~~~~~~~~~~~~~\n", philo->id);
	ft_usleep(philo, info->argu[TIME_TO_EAT]);
	print_action(DONE_EAT, philo);

	// finish eating
	pthread_mutex_unlock(&info->fork[snd].mutex);
	pthread_mutex_unlock(&info->fork[fst].mutex);
	info->fork[snd].status = UNLOCK;
	info->fork[fst].status = UNLOCK;
}

void	sleeping(t_philo *philo)
{
	if (philo->info->share_status == DEAD)
		return ;
	print_action(SLEEPING, philo);
	ft_usleep(philo, philo->info->argu[TIME_TO_SLEEP]);
	print_action(DONE_SLEEP, philo);
}

void	thinking(t_philo *philo)
{
	if (philo->info->share_status == DEAD)
		return ;
	print_action(THINKING, philo);
}

void	*routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	printf("%d is in routine!!!\n", philo->id);
	philo->info->share_status ++;
	while (philo->info->share_status != ALIVE)
		gettimeofday(&philo->time, NULL);
	gettimeofday(&philo->time, NULL);
	if (philo->id %2 == 0)
		ft_usleep(philo, 200);
	while (philo->info->share_status == ALIVE)
	{
		eating(philo, philo->info);
		sleeping(philo);
		thinking(philo);
		// ft_usleep(philo, 200);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_info		info;
	t_philo		*philo;
	pthread_t	*pthread;
	int			i;

	if (argv_check(argc, argv, info.argu) == -1 ||\
	 init_vars(&info, &philo, &pthread) == -1)
	{
		printf("error\n");
		return (1); // free philo, fork
	}
	for (int i = 0; i < 5; i++)
		printf("[%d]", info.argu[i]);
	printf("\n");
	
	i = 0;
	while (++i <= info.argu[NUMBER_OF_PHILOS])
	{
		if (pthread_create(&pthread[i], NULL, routine, &philo[i]) != 0)
			printf("<%d> create fail\n", i); // fail 경우 detach?
	}
	while (1)
	{
		if (info.share_status == info.argu[NUMBER_OF_PHILOS])
		{
			printf("all thread is in routine!!!!!!!!!!!!!!!!!!!\n");
			info.share_status = ALIVE;
			gettimeofday(&info.start_time, NULL);
			break ;
		}
	}
	status_monitoring(&info, philo);
	printf("will detach!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	for (int i = 1; i <= info.argu[NUMBER_OF_PHILOS]; i++)
	{
		if (pthread_detach(pthread[i]) != 0) // 바로 종료
			printf("----%d detaching fail----\n", i);
	}
	printf("detach all success\n");
	// double_free();
}
