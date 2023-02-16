/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 11:17:50 by hyoh              #+#    #+#             */
/*   Updated: 2023/02/16 10:32:46 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	getting_fork(t_philo *philo, t_info *info, int *fst, int *snd)
{
	*fst = philo->id;
	*snd = philo->id + 1;
	if (philo->id == info->argu[NUMBER_OF_PHILOS]) // 총 한명일 때, 마지막 num일 때
		*snd = 1;
	while (1)
	{ // freeze 되기 전에 lock or unlock 판별
		if (*fst != *snd && info->fork[*fst].status == UNLOCK \
				&& info->fork[*snd].status == UNLOCK)
			break ;
		if (info->argu[TIME_TO_DIE] < get_time_diff(philo))
		{
			print_action(DYING, philo);
			info->share_status = DEAD;
			printf("	was waiting for fork\n");
			return (-1);
		}
	}
	pthread_mutex_lock(&info->fork[*fst].mutex);
	pthread_mutex_lock(&info->fork[*snd].mutex);
	info->fork[*fst].status = LOCK;
	info->fork[*snd].status = LOCK;
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
	gettimeofday(&philo->time, NULL);
	print_action(EATING, philo);
	usleep(info->argu[TIME_TO_EAT] * 1000);

	// finish eating
	philo->rest_num--;
	if (philo->rest_num == 0)
		printf("  %d done eating~~~~~~~~~~~~~~~~~~~~~~~\n", philo->id);
	if (info->argu[TIME_TO_DIE] < get_time_diff(philo))
	{
		print_action(DYING, philo);
		info->share_status = DEAD;
		printf("	was eating\n");
	}
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

	usleep(philo->info->argu[TIME_TO_SLEEP] * 1000);
	if (philo->info->argu[TIME_TO_DIE] < get_time_diff(philo))
	{
		print_action(DYING, philo);
		philo->info->share_status = DEAD;
		printf("	was sleeping\n");
	}
	// for (int i = 0; i < philo->argu[TIME_TO_SLEEP]; i++)
	// {
	// 	usleep(1000);
	// 	if (philo->argu[TIME_TO_DIE] < get_time_diff(philo))
	// 	{
	// 		print_action(DYING, philo);
	// 		*philo->share = 1;
	// 	}
	// }
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
	gettimeofday(&philo->time, NULL);
	printf("%d is in routine\n", philo->id);
	while (philo->info->share_status == ALIVE)
	{
		eating(philo, philo->info);
		sleeping(philo);
		thinking(philo);
		usleep(100); //
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
		// free philo, fork
		return (1);
	}
	gettimeofday(&info.start_time, NULL);
	
	i = 0;
	while (++i <= info.argu[NUMBER_OF_PHILOS])
	{
		if (pthread_create(&pthread[i], NULL, routine, &philo[i]) != 0)
			printf("<%d> create fail\n", i);
		
		pthread_detach(pthread[i]); // 스레드 끝날 때까지 기다림
	}

	status_monitoring(&info, philo);
	i = 0;
	while (++i <= info.argu[NUMBER_OF_PHILOS])
		pthread_join(pthread[i], NULL); // 바로 종료
	// double_free();
}
