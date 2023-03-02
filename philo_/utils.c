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

// us -> ms -> s

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

int	get_cur_time(t_philo *philo) // 없애기
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

	t_time tmp1;
	gettimeofday(&tmp1, NULL);
	goal = get_cur_time(philo) + wait;
	while(1)
	{
		if (goal <= get_cur_time(philo))
			break ;
		if (is_dead(philo) == 1)
			break ;
		usleep(100);
	}
	t_time tmp2;
	gettimeofday(&tmp2, NULL);
	// printf("	%d [%d] ft_usleep for %d (goal was %d)\n", get_cur_time(philo), philo->id, diff(tmp1, tmp2), goal);
	return (0);
}

void	print_action(int action, t_philo *philo)
{
	t_time	cur;
	gettimeofday(&cur, NULL);
	int cur_time = diff(philo->info->start_time, cur);

	int rest_time = get_rest_time(philo);
	
	if (action == TAKING_FORK)
		printf("%d [%d] has taken a fork <%d>\n", cur_time, philo->id, rest_time);
	else if (action == EATING)
		printf("%d [%d] is eating <%d> (rest num: %d)------\n", cur_time, philo->id, rest_time, philo->rest_num);
	else if (action == SLEEPING)
		printf("%d [%d] is sleeping <%d>\n", cur_time, philo->id, rest_time);
	else if (action == THINKING)
		printf("%d [%d] is thinking <%d>\n", cur_time, philo->id, rest_time);
	else if (action == DYING)
		printf("%d [%d] died <%d>\n", cur_time, philo->id, rest_time);
	// else if (action == READY_FORK)
	// 	printf("%d [%d] is ready for forks!!\n", cur_time, philo->id);
	// else if (action == DONE_EAT)
	// 	printf("%d [%d] finished eating\n", cur_time, philo->id);
	// else if (action == DONE_SLEEP)
	// 	printf("%d [%d] finished sleeping\n", cur_time, philo->id);
	// else if (action == WAITING_FORK)
	// 	printf("%d [%d] is waiting fork\n", cur_time, philo->id);
	// else
	// 	printf("print_action error ! !\n");
}
