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
	pthread_mutex_lock(&(info->print));
	printf("%d [%d] has taken a fork\n", get_cur_time(philo), philo->id); // taken A fork 니까 하나 집을 때마다 출력하게 바꾸기
	pthread_mutex_unlock(&(info->print));
	return (0);
}

void	eating(t_philo *philo, t_info *info)
{
	int	fst;
	int	snd;

	if (getting_fork(philo, info, &fst, &snd) == -1)
		return ;
	philo->rest_num--;
	gettimeofday(&philo->time, NULL);
	pthread_mutex_lock(&(info->print));
	printf("%d [%d] is eating ------\n", get_cur_time(philo), philo->id);
	pthread_mutex_unlock(&(info->print));
	if (philo->rest_num == 0)
		printf("  %d satisfied must eat num~~~~~~~~~~~~~~~~~~~\n", philo->id);
	ft_usleep(philo, info->argu[TIME_TO_EAT]);
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

void	sleeping(t_philo *philo, t_info *info)
{
	pthread_mutex_lock(&(info->print));
	printf("%d [%d] is sleeping\n", get_cur_time(philo), philo->id);
	pthread_mutex_unlock(&(info->print));
	ft_usleep(philo, info->argu[TIME_TO_SLEEP]);
}

void	thinking(t_philo *philo, t_info *info)
{
	pthread_mutex_lock(&(info->print));
	printf("%d [%d] is thinking\n", get_cur_time(philo), philo->id);
	pthread_mutex_unlock(&(info->print));
	usleep(80);
}

void	*routine(void *param)
{
	t_philo	*philo;
	t_info	*info;

	philo = (t_philo *)param;
	info = philo->info;
	info->ready_philo_num ++;
	while (info->ready_philo_num != info->argu[NUMBER_OF_PHILOS])
		continue ;
		// gettimeofday(&philo->time, NULL);
	gettimeofday(&philo->time, NULL);
	if (philo->id %2 == 0)
		usleep(50);
	while (1)
	{
		eating(philo, philo->info);
		sleeping(philo, philo->info);
		thinking(philo, philo->info);
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
	i = 0;
	while (++i <= info.argu[NUMBER_OF_PHILOS])
	{
		if (pthread_create(&pthread[i], NULL, routine, &philo[i]) != 0)
			printf("<%d> create fail\n", i); // fail 경우 detach?
	}
	while (info.ready_philo_num != info.argu[NUMBER_OF_PHILOS])
		continue ;
	gettimeofday(&info.start_time, NULL);
	usleep(50);
	status_monitoring(&info, philo);
	for (int i = 1; i <= info.argu[NUMBER_OF_PHILOS]; i++)
	{
		if (pthread_detach(pthread[i]) != 0) // 바로 종료
			printf("----%d detaching fail----\n", i);
		// mutex_unlock -> mutex_destroy(unlock상태여야 함)
	}
	printf("-----detach all success-----\n");
	return (0);
	// system("leaks ./philo");
	// double_free();
	// ps -eLf | grep testsrv
}
