/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 12:19:12 by hyoh              #+#    #+#             */
/*   Updated: 2023/02/24 09:23:59 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int diff(t_time old, t_time new)
{
	long long	oldms;
	long long	newms;
	int			ret;

	oldms = old.tv_sec * 1000 + old.tv_usec / 1000;
	newms = new.tv_sec * 1000 + new.tv_usec / 1000;
	ret = newms - oldms;
	return (ret);
}

int	get_cur_time(t_philo *philo)
{
	t_time	cur;

	gettimeofday(&cur, NULL);
	return (diff(philo->info->start_time, cur));
}

int	get_rest_time(t_philo *philo)
{
	t_time	cur;
	int		passed;

	gettimeofday(&cur, NULL);
	passed = diff(philo->time, cur);
	return (philo->info->argu[TIME_TO_DIE] - passed);
}

int	ft_usleep(t_philo *philo, int wait)
{
	int	goal;

	goal = get_cur_time(philo) + wait;
	while(1)
	{
		if (goal <= get_cur_time(philo))
			break ;
		usleep(100);
	}
	return (0);
}

void	status_monitoring(t_info *info, t_philo *philos)
{
	int		i;
	int		flag;

	while (1)
	{
		i = 0;
		flag = 1;
		while (++i <= info->argu[NUMBER_OF_PHILOS])
		{
			if (get_rest_time(&philos[i]) < 0)
			{
				pthread_mutex_lock(&(info->print));
				printf("%d [%d] died\n", get_cur_time(&philos[i]), philos[i].id);
				return ;
			}
			if (philos[i].rest_num > 0)
				flag = 0;
		}
		if (info->argu[MIN_TO_EAT] != -1 && flag == 1)
		{
			printf(" --- everyone ate ---\n");
			pthread_mutex_lock(&(info->print));
			return ;
		}
		usleep(500);
	}
}
