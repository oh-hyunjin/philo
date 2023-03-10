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

void	*death_check_thr(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	while (get_rest_time(philo->info, philo) > 0)
		usleep(10);
	printf("%d is died\n", philo->id);
	exit(0);
	// philo->status = DEAD;
}

void	action(t_info *info, t_philo *philo)
{
	// int	status;
	pthread_t tmp;

	printf("[%d] is in action\n", philo->id);
	philo->time = get_cur_time(info);
	philo->status = ALIVE;
	pthread_create(&tmp, NULL, death_check_thr, philo);
	while (philo->status == ALIVE) // 타인이 죽으면 kill all에서 끝냄
	{
		taking_fork(info, philo);
		eating(info, philo);
		sleeping(info, philo);
		thinking(info, philo);
	}
	pthread_detach(tmp);
	printf("[%d] exit\n", philo->id);
	exit(0);
}

void	*full_monitoring_thr(void *param)
{
	t_info *info;
	int	i;

	info = (t_info *)param;
	i = 0;
	while (++i <= info->argu[NUMBER_OF_PHILOS])
	{
		printf("will wait full sem\n");
		sem_wait(info->full);
		printf("someone satisfied\n");
	}
	printf("full !!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	return (0);
}

void	status_monitoring(t_philo *philo)
{
	pthread_t	full_thr;
	int			tmp;

	pthread_create(&full_thr, NULL, full_monitoring_thr, philo->info);
	waitpid(-1, &tmp, 0);
	pthread_detach(full_thr);
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

	usleep(100);
	printf("@"); // 부모에서 한 번만 출력돼야 한다. 자식은 exit됨
	status_monitoring(philos);
	int i = 0;
	while (++i <= info.argu[NUMBER_OF_PHILOS])
	{
		kill(pids[i], SIGKILL);
		printf("killed [i]\n");
	}
}

//sem : every fork, full_flag