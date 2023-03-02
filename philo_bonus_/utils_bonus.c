/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 09:03:32 by hyoh              #+#    #+#             */
/*   Updated: 2023/02/25 12:20:21 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	is_dead(t_info *info, t_philo *philo)
{
	if (info->share_status != ALIVE)
		return (1);
	if (get_rest_time(info, philo) < 0)
	{
		info->share_status = DEAD;
		printf("%lld [%d] died\n", get_cur_time(info), philo->id);
		return (1);
	}
	return (0);
}

long long	get_cur_time(t_info *info)
{
	//now-start
	t_time		now;
	long long	now_time;

	gettimeofday(&now, NULL);
	now_time = now.tv_sec * 1000 + now.tv_usec / 1000;
	if (info->share_status == READY)
		return (now_time);
	return (now_time - info->start_time);
}

long long	get_rest_time(t_info *info, t_philo *philo)
{
	long long	elapsed_time;

	elapsed_time = get_cur_time(info) - philo->time;
	return (info->argu[TIME_TO_DIE] - elapsed_time);
}

int	ft_usleep(t_info *info, t_philo *philo, int wait)
{
	long long	goal;

	goal = get_cur_time(info) + wait;
	while(1)
	{
		if (goal <= get_cur_time(info))
			break ;
		if (is_dead(info, philo) == 1)
			break ;
		usleep(100);
	}
	// printf("	%d [%d] ft_usleep for %d (goal was %d)\n", get_cur_time(philo), philo->id, diff(tmp1, tmp2), goal);
	return (0);
}
