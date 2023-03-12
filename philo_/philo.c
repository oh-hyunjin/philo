/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 11:17:50 by hyoh              #+#    #+#             */
/*   Updated: 2023/03/12 22:15:00 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_fork(t_info *info, t_fork *target_fork)
{
	while (info->share_status == ALIVE)
	{
		if (target_fork->status == UNLOCK)
		{
			target_fork->status = LOCK;
			pthread_mutex_lock(&(target_fork->mutex));
			return ;
		}
		usleep(300);
	}
}

void	getting_fork(t_philo *philo, t_info *info, int *fst, int *snd)
{
	*fst = philo->id;
	*snd = philo->id + 1;
	if (philo->id == info->argu[NUM_OF_PHILOS]) // 총 한명일 때, 마지막 philo id일 때
		*snd = 1;
	if (philo->id % 2 == 1)
	{
		lock_fork(info, &(info->fork[*fst]));
		lock_fork(info, &(info->fork[*snd]));
	}
	else
	{
		lock_fork(info, &(info->fork[*snd]));
		lock_fork(info, &(info->fork[*fst]));
	}
	if (info->share_status != ALIVE)
	{
		pthread_mutex_unlock(&info->fork[*fst].mutex);
		info->fork[*fst].status = UNLOCK;
		pthread_mutex_unlock(&info->fork[*snd].mutex);
		info->fork[*snd].status = UNLOCK;
		return;
	}
	printf("%d [%d] has taken a fork <%d>\n", get_cur_time(philo), philo->id, get_rest_time(philo));
	// taken A fork 니까 하나 집을 때마다 출력하게 바꾸기
	return;
}

void	eating(t_philo *philo, t_info *info)
{
	int	fst;
	int	snd;

	getting_fork(philo, info, &fst, &snd);
	if (info->share_status != ALIVE)
		return ;
	philo->rest_num--;
	gettimeofday(&philo->time, NULL);
	printf("%d [%d] is eating ------\n", get_cur_time(philo), philo->id);
	if (philo->rest_num == 0)
		printf("  %d satisfied must eat num~~~~~~~~~~~~~~~~~~~\n", philo->id);
	ft_usleep(philo, info->argu[TIME_TO_EAT]);
	if (philo->id % 2 == 1)
	{
		pthread_mutex_unlock(&info->fork[snd].mutex);
		info->fork[snd].status = UNLOCK;
		pthread_mutex_unlock(&info->fork[fst].mutex);
		info->fork[fst].status = UNLOCK;
	}
	else
	{
		pthread_mutex_unlock(&info->fork[fst].mutex);
		info->fork[fst].status = UNLOCK;
		pthread_mutex_unlock(&info->fork[snd].mutex);
		info->fork[snd].status = UNLOCK;
	}
}

void	sleeping(t_philo *philo, t_info *info)
{
	if (info->share_status != ALIVE)
		return ;
	printf("%d [%d] is sleeping\n", get_cur_time(philo), philo->id);
	ft_usleep(philo, info->argu[TIME_TO_SLEEP]);
}

void	thinking(t_philo *philo, t_info *info)
{
	if (info->share_status != ALIVE)
		return ;
	printf("%d [%d] is thinking\n", get_cur_time(philo), philo->id);
	usleep(300);
}

void	*routine(void *param)
{
	t_philo	*philo;
	t_info	*info;

	philo = (t_philo *)param;
	info = philo->info;
	info->share_status ++;
	while (info->share_status != ALIVE)
		continue ;
	gettimeofday(&philo->time, NULL);
	if (philo->id % 2 == 0)
		usleep(300);
	while (info->share_status == ALIVE)
	{
		eating(philo, philo->info);
		sleeping(philo, philo->info);
		thinking(philo, philo->info);
	}
	return (0);
}
