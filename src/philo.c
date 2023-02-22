/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 11:17:50 by hyoh              #+#    #+#             */
/*   Updated: 2023/02/22 13:00:55 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	getting_fork(t_philo *philo, t_info *info, int *fst, int *snd)
{
	*fst = philo->id;
	*snd = philo->id + 1;
	if (philo->id == info->argu[NUMBER_OF_PHILOS]) // 총 한명일 때, 마지막 philo id일 때
		*snd = 1;
	// 홀 : fst먼저
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(&info->fork[*fst].mutex);
		pthread_mutex_lock(&info->fork[*snd].mutex);
	}
	else
	{
		pthread_mutex_lock(&info->fork[*snd].mutex);
		pthread_mutex_lock(&info->fork[*fst].mutex);
	}

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
	if (philo->id % 2 == 1)
	{
		pthread_mutex_unlock(&info->fork[snd].mutex);
		pthread_mutex_unlock(&info->fork[fst].mutex);
	}
	else
	{
		pthread_mutex_unlock(&info->fork[fst].mutex);
		pthread_mutex_unlock(&info->fork[snd].mutex);
	}
	
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
	philo->info->share_status ++; // 이것도 공유 자원..?
	while (philo->info->share_status != ALIVE)
		gettimeofday(&philo->time, NULL);
	gettimeofday(&philo->time, NULL);
	if (philo->id %2 == 0)
		usleep(50);
	while (philo->info->share_status == ALIVE)
	{
		eating(philo, philo->info);
		sleeping(philo);
		thinking(philo);
		usleep(50);
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
	usleep(50);
	status_monitoring(&info, philo);
	printf("will detach!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	for (int i = 1; i <= info.argu[NUMBER_OF_PHILOS]; i++)
	{
		if (pthread_detach(pthread[i]) != 0) // 바로 종료
			printf("----%d detaching fail----\n", i);
		// mutex_unlock -> mutex_destroy(unlock상태여야 함)
	}
	printf("detach all success\n");
	// double_free();
}
