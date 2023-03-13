/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:51:26 by hyoh              #+#    #+#             */
/*   Updated: 2023/03/13 15:46:51 by hyoh             ###   ########.fr       */
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

void	unlock_fork(t_fork *target_fork)
{
	target_fork->status = UNLOCK;
	pthread_mutex_unlock(&(target_fork->mutex));
}

void	getting_fork(t_philo *philo, t_info *info, int *fst, int *snd)
{
	*fst = philo->id;
	*snd = philo->id + 1;
	if (philo->id == info->argu[NUM_OF_PHILOS])
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
	if (info->share_status != ALIVE) // 이걸 lock_fork()에 넣기
	{
		unlock_fork(&info->fork[*fst]);
		unlock_fork(&info->fork[*snd]);
		return ;
	}
	printf("%d [%d] has taken a fork\n", get_cur_time(philo), philo->id);
	// taken A fork 니까 하나 집을 때마다 출력하게 바꾸기
	return ;
}
