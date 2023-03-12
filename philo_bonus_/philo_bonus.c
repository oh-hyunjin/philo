/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 12:14:37 by hyoh              #+#    #+#             */
/*   Updated: 2023/03/12 18:26:17 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*death_check_thr(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	while (get_rest_time(philo->info, philo) > 0)
		usleep(100);
	sem_wait(philo->info->print);
	printf("%d [%d] died\n", get_cur_time(philo->info), philo->id);
	exit(0);
	return (0);
}

void	action(t_info *info, t_philo *philo)
{
	pthread_t tmp;

	philo->time = get_cur_time(info);
	pthread_create(&tmp, NULL, death_check_thr, philo);
	while (1)
	{
		taking_fork(info, philo);
		eating(info, philo);
		sleeping(info, philo);
		thinking(info, philo);
		usleep(500);
	}
	printf("detach [%d] death check thread res : %d\n", philo->id, pthread_detach(tmp));
	printf("[%d] exit\n", philo->id);
	exit(0);
}

void	*full_monitoring_thr(void *param)
{
	t_info *info;
	int	i;

	info = (t_info *)param;
	i = 0;
	printf("full monitoring start : %d\n", info->argu[NUM_OF_PHILOS]);
	while (++i <= info->argu[NUM_OF_PHILOS])
		sem_wait(info->full);
	info->status = FULL;
	sem_wait(info->print);
	printf("full !!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	return (0);
}

void	*dead_monitoring_thr(void *param)
{
	t_info *info;
	int		tmp;

	info = (t_info *)param;
	waitpid(-1, &tmp, 0);
	if (info->status == ALIVE)
	{
		info->status = DEAD;
		printf("!!!!!!!!!!!somone died!!!!!!!!!!!!!!\n");
	}
	return (0);
}

void	status_monitoring(t_info *info)
{
	pthread_t	full_thr;
	pthread_t	dead_thr;

	info->status = ALIVE;
	pthread_create(&full_thr, NULL, full_monitoring_thr, info);
	pthread_create(&dead_thr, NULL, dead_monitoring_thr, info);

	while (info->status == ALIVE)
		continue ;
	pthread_detach(full_thr);
	pthread_detach(dead_thr);
}

int	main(int argc, char **argv)
{
	t_info	info;
	t_philo	*philos;
	pid_t	*pids;

	if (argv_check(argc, argv, &info) < 0 || sem_set(&info) < 0 \
			|| init(&info, &philos, &pids) < 0)
	{
		printf("error\n");
		return (0);
	}
	printf("init clear\n");

	status_monitoring(&info);	

	int i = 0;
	// kill(0, SIGKILL);
	while (++i <= info.argu[NUM_OF_PHILOS])
	{
		kill(pids[i], SIGKILL);
		// printf("killed [%d]\n", i);
	}
}

//sem : every fork, full_flag