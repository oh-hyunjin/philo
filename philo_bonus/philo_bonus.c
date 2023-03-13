/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 12:14:37 by hyoh              #+#    #+#             */
/*   Updated: 2023/03/13 15:58:24 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*death_check_in_action(void *param)
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
	// printf("%lld [%d] is in action\n", philo->time, philo->id);
	pthread_create(&tmp, NULL, death_check_in_action, philo);
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
	t_info	*info;
	int		i;

	info = (t_info *)param;
	i = 0;
	printf("full monitoring start : %d\n", info->argu[NUM_OF_PHILOS]);
	while (info->status == ALIVE && ++i <= info->argu[NUM_OF_PHILOS])
		sem_wait(info->full);
	if (info->status != ALIVE)
	{
		printf("exit f_m_t\n");
		return (0);
	}
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
	printf("exit d_m_t\n");
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
	printf("\nwill detach full_thr, dead_thr\n");
	if (pthread_detach(full_thr) == 0)
		printf("full detach success~~~~~~\n");
	else
		printf("full detach fail!!!!!!!!!!!!\n");
	if (pthread_detach(dead_thr) == 0)
		printf("dead detach success~~~~~~\n");
	else
		printf("dead detach fail!!!!!!!!!!!!\n");
}

void	kill_all(t_info *info, pid_t *pids)
{
	int i;

	printf("\nkill all start\n");
	i = 0;
	while (++i <= info->argu[NUM_OF_PHILOS])
	{
		if (kill(pids[i], SIGKILL) == -1)
			printf("kill [%d] fail!!!!!!!!!!!!!! : %s\n", i, strerror(errno));
		else
			printf("kill [%d] success~~~~\n", i);
	}
	printf("kill clear\n\n");
	// sem close -> unlink
	printf("sem fork close res : %d\n", sem_close(info->fork));
	printf("sem print close res : %d\n", sem_close(info->print));
	printf("sem full close res : %d\n\n", sem_close(info->full));

	printf("sem fork unlink res : %d\n", sem_unlink("fork"));
	printf("sem print unlink res : %d\n", sem_unlink("print"));
	printf("sem full unlink res : %d\n", sem_unlink("full"));
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
	status_monitoring(&info);
	kill_all(&info, pids);
	printf("--- fin ---\n");
	// system("leaks philo_bonus");
}

// pthread detach가 정확히 어떻게 작동하는지...