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

int	get_cur_time(t_info *info)
{
	//now-start
	t_time		now;
	int			now_time;

	gettimeofday(&now, NULL);
	now_time = now.tv_sec * 1000 + now.tv_usec / 1000;
	if (info->start_time == 0)
		return (now_time);
	return (now_time - info->start_time);
}

int	get_rest_time(t_info *info, t_philo *philo)
{
	long long	elapsed_time;

	elapsed_time = get_cur_time(info) - philo->time;
	return (info->argu[TIME_TO_DIE] - elapsed_time);
}

int	ft_usleep(t_philo *philo, int wait)
{
	int	goal;

	int tmp = get_cur_time(philo->info);
	goal = tmp + wait;
	while(1)
	{
		if (goal <= get_cur_time(philo->info))
			break ;
		// if (is_dead(info, philo) == 1)
		// 	break ;
		usleep(10);
	}
	// printf("	%d [%d] ft_usleep for %d (goal was %d)\n", get_cur_time(philo), philo->id, diff(tmp1, tmp2), goal);
	return (0);
}
