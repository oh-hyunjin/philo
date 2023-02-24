/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 09:42:55 by hyoh              #+#    #+#             */
/*   Updated: 2023/02/23 12:24:25 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philo)
{
	if (philo->info->share_status != ALIVE)
	{
		return (1);
	}
	if (get_rest_time(philo) < 0) // =안해도 되나
	{
		philo->info->share_status = DEAD;
		print_action(DYING, philo);
		return (1);
	}
	return (0);
}

void	status_monitoring(t_info *info, t_philo *philo)
{
	int		i;
	int		flag;
	t_time	cur;

	while (1)
	{
		i = 0;
		flag = 1;
		while (++i <= info->argu[NUMBER_OF_PHILOS])
		{
			gettimeofday(&cur, NULL);
			if (is_dead(&philo[i]) == 1)
			{
				gettimeofday(&cur, NULL);
				printf("%d --- someone died ---\n", diff(info->start_time, cur));
				return ;	
			}
			if (philo[i].rest_num > 0)
				flag = 0;
		}
		if (info->argu[MIN_TO_EAT] != -1 && flag == 1)
		{
			info->share_status = FULL;
			gettimeofday(&cur, NULL);
			printf("%d --- everyone lived ---\n", diff(info->start_time, cur));
			return ;
		}
		usleep(100); // gettimeofday 함수 텀 주기
	}
}
