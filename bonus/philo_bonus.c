/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 12:14:37 by hyoh              #+#    #+#             */
/*   Updated: 2023/02/25 12:18:03 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	action(t_info *info, t_philo *philo)
{
	printf("share status pointer : %p\n", &info->share_status);
	while(info->share_status == READY)
		continue ;
	printf("	[%d] action start !\n", philo->id);
	philo->time = get_cur_time(info);
	while (info->share_status == ALIVE)
	{
		taking_fork(info, philo);
		eating(info, philo);
		sleeping(info, philo);
		thinking(info, philo);
	}
	printf("[%d] exit\n", philo->id);
	exit(0);
}

void status_monitoring(t_info *info, t_philo *philos)
{
	int	i;
	int	full_flag;

	while (1)
	{
		if (info->share_status != ALIVE)
			return ;
		i = 0;
		full_flag = 1;
		while (++i <= info->argu[NUMBER_OF_PHILOS])
		{
			if (is_dead(info, &philos[i]) == 1)
				return ;
			if (philos[i].rest_num > 0)
				full_flag = 0;
		}
		if (info->argu[MIN_TO_EAT] != -1 && full_flag == 1)
		{
			info->share_status = FULL;
			return ;
		}
		// usleep(100);
	}
}

int	main(int argc, char **argv)
{
	t_info	info;
	t_philo	*philos;
	// int		status;

	if (argv_check(argc, argv, &info) < 0 || init(&info, &philos) < 0)
	{
		printf("error\n");
		return (0);
	}

	printf("share status pointer(in main) : %p\n", &info.share_status);
	info.start_time = get_cur_time(&info);
	printf("start!\n");
	info.share_status = ALIVE;

	//usleep
	// status_monitoring(&info, philos);
	// while (wait(&status) != -1)
		// continue ;

	// free variables
	// sem_close(info.fork);
	// sem_unlink("fork");
}
