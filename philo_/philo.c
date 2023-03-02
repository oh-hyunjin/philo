/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 11:17:50 by hyoh              #+#    #+#             */
/*   Updated: 2023/02/24 09:25:42 by hyoh             ###   ########.fr       */
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
		pthread_mutex_lock(&info->fork[*fst]);
		pthread_mutex_lock(&info->fork[*snd]);
	}
	else
	{
		pthread_mutex_lock(&info->fork[*snd]);
		pthread_mutex_lock(&info->fork[*fst]);
	}
	if (is_dead(philo) == 1) // unlock?
		return (-1);
	print_action(TAKING_FORK, philo); // taken A fork 니까 하나 집을 때마다 출력하게 바꾸기
	// printf("	(in gettinf_fork) [%d] rest:%d, cur:%d\n", philo->id, get_rest_time(philo), get_cur_time(philo));
	return (0);
}

void	eating(t_philo *philo, t_info *info)
{
	int	fst;
	int	snd;

	if (is_dead(philo) == 1)
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
		pthread_mutex_unlock(&info->fork[snd]);
		pthread_mutex_unlock(&info->fork[fst]);
	}
	else
	{
		pthread_mutex_unlock(&info->fork[fst]);
		pthread_mutex_unlock(&info->fork[snd]);
	}
}

void	sleeping(t_philo *philo)
{
	if (is_dead(philo) == 1)
		return ;
	print_action(SLEEPING, philo);
	ft_usleep(philo, philo->info->argu[TIME_TO_SLEEP]);
	print_action(DONE_SLEEP, philo);
}

void	thinking(t_philo *philo)
{
	if (is_dead(philo) == 1)
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
	while (is_dead(philo) == 0)
	{
		eating(philo, philo->info);
		sleeping(philo);
		thinking(philo);
		usleep(80);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_info		info;
	t_philo		*philo;
	pthread_t	*pthread;
	int			i;

	if (argv_check(argc, argv, info.argu) == -1 ||
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
			break ;
		}
	}
	info.share_status = ALIVE;
	gettimeofday(&info.start_time, NULL);
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
	// system("leaks ./philo");
	// double_free();
	// ps -eLf | grep testsrv
}
