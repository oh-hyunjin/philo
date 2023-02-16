/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 12:19:12 by hyoh              #+#    #+#             */
/*   Updated: 2023/02/16 09:48:21 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int	num; // unint?

	if (str == NULL)
		return (-1);
	num = 0;
	while (*str)
	{
		if (*str - '0' < 0 || *str - '0' > 9)
			return (-1);
		num = 10 * num + (*str - '0');
		str++;
	}
	return (num);
}

void	print_action(int action, t_philo *philo)
{
	t_time	cur_time;
	int		now;
	int		rest_time;

	gettimeofday(&cur_time, NULL);
	now = cur_time.tv_usec / 1000;
	rest_time = philo->info->argu[TIME_TO_DIE] - get_time_diff(philo);
	int rest_eat = philo->rest_num;

	if (action == TAKING_FORK)
		printf("%d [%d] has taken a fork <%d> (%d)\n", now, philo->id, rest_time, rest_eat);
	else if (action == EATING)
		printf("%d [%d] is eating <%d> (%d)\n", now, philo->id, rest_time, rest_eat);
	else if (action == SLEEPING)
		printf("%d [%d] is sleeping <%d> (%d)\n", now, philo->id, rest_time, rest_eat);
	else if (action == THINKING)
		printf("%d [%d] is thinking <%d> (%d)\n", now, philo->id, rest_time, rest_eat);
	else if (action == DYING)
		printf("%d [%d] died <%d> (%d)!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n", now, philo->id, rest_time, rest_eat);
}

int	get_time_diff(t_philo *philo)
{
	t_time	cur;
	int		diff;

	gettimeofday(&cur, NULL);
	diff = (cur.tv_sec - philo->time.tv_sec) * 1000\
		 + ((cur.tv_usec - philo->time.tv_usec ) / 1000);
	// printf("diff: %d\n", diff);
	return (diff);
}

void	status_monitoring(t_info *info, t_philo *philo)
{
	int	flag;

	// (void)philo;
	while (1)
	{
		// when someone died
		if (info->share_status == DEAD)
		{
			printf("--- someone died ---\n");
			return ;
		}

		// when everyone ate min
		if (info->argu[MIN_TO_EAT] == -1)
			continue ;
		flag = 0;
		for (int i = 1; i <= info->argu[NUMBER_OF_PHILOS]; i++)
		{
			if (philo[i].rest_num != 0)
				flag = 1;
		}
		if (flag == 0)
		{
			printf("--- everyone lived ---\n");
			return ;
		}
	}
}

int	init_vars(t_info *info, t_philo **philo, pthread_t **pthread)
{
	int	i;

	info->fork = (t_fork *)malloc \
		(sizeof(t_fork) * (info->argu[NUMBER_OF_PHILOS] + 1));
	*philo = (t_philo *)malloc \
		(sizeof(t_philo) * (info->argu[NUMBER_OF_PHILOS] + 1));
	*pthread = (pthread_t *)malloc \
		(sizeof(pthread_t) * (info->argu[NUMBER_OF_PHILOS] + 1));
	if (info->fork == NULL || philo == NULL || pthread == NULL) // 맞나?
		return (-1);

	info->share_status = 0;
	i = 0;
	while (++i <= info->argu[NUMBER_OF_PHILOS]) // from 1
	{
		// fork
		info->fork[i].status = UNLOCK;
		if (i != info->argu[NUMBER_OF_PHILOS] && \
			pthread_mutex_init(&(info->fork[i]).mutex, NULL) == -1)
				return (-1);
		// philo
		(*philo)[i].id = i;
		(*philo)[i].rest_num = info->argu[MIN_TO_EAT];
		(*philo)[i].info = info;
	}
	return (0);
}

int	argv_check(int argc, char **argv, int argu[5])
{
	int	i;

	i = -1;
	while (++i < argc - 1)
	{
		argu[i] = ft_atoi(argv[i + 1]);
		if (argu[i] == -1)
			return (-1);
	}
	if (argc == 5)
		argu[MIN_TO_EAT] = -1;
	return (0);
}
