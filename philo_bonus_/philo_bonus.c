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

int full_check(t_info *info)
{
	int	i;

	i = info->argu[NUMBER_OF_PHILOS];
	while (i--)
		sem_wait(info->is_full);
	info->status = FULL;
	printf("full !!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	return (0);
}

int dead_check(t_info *info)
{
	int	status;

	waitpid(0, &status, 0);
	info->status = DEAD;
	printf("someone died !!!!!!!!!!!!!!!!!!!\n");
	return (0);
}

void	kill_all(t_info *info, t_philo **philo, int **pid)
{
	// pthread join or detach, kill every philo, sem_close,unlink
}

int	main(int argc, char **argv)
{
	t_info	info;
	t_philo	*philos;
	int		*pids;

	if (argv_check(argc, argv, &info) < 0 || init(&info, &philos, &pids) < 0)
	{
		printf("error\n");
		return (0);
	}

	info.start_time = get_cur_time(&info);
	printf("start!\n");
	pthread_create(full_check); // thread
	pthread_create(dead_check); // thread
	
	while (info.status != ALIVE)
		continue ;
	kill_all(&info, &philos, &pids);
}

//sem : every fork, full_flag, dead_flag