/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 12:19:12 by hyoh              #+#    #+#             */
/*   Updated: 2023/02/21 10:59:47 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// us -> ms -> s

unsigned int diff(t_time old, t_time new)
{
	unsigned int oldms;
	unsigned int newms;

	oldms = old.tv_sec * 1000 + old.tv_usec / 1000;
	newms = new.tv_sec * 1000 + new.tv_usec / 1000;
	return (newms - oldms);
}

int cur_time(t_philo *philo)
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

// int	ft_usleep(t_philo *philo, int wait)
// {
// 	int	goal;

// 	t_time tmp1;
// 	gettimeofday(&tmp1, NULL);
// 	goal = cur_time(philo) + wait;
// 	while(goal > cur_time(philo))
// 	{
// 		if (get_rest_time(philo) <= 0)
// 		{
// 			print_action(DYING, philo);
// 			philo->info->share_status = DEAD;
// 			return (-1);
// 		}
// 		print_action(USLEEP, philo);
// 	}
// 	t_time tmp2;
// 	gettimeofday(&tmp2, NULL);
// 	printf("	%d [%d] ft_usleep for %d (goal was %d))\n", cur_time(philo), philo->id, diff(tmp1, tmp2), goal);
// 	return (0);
// }

long long	get_time(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

/* Same as usleep but more precise with big numbers */
int	ft_usleep(t_philo *philo, long long wait)
{
	long long	start;

	start = get_time();
	while (get_time() < start + wait)
	{
		if (get_rest_time(philo) <= 0)
		{
			print_action(DYING, philo);
			philo->info->share_status = DEAD;
			return (-1);
		}
		usleep(10);
	}
	return (0);
}

int ms(t_time time)
{
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	print_action(int action, t_philo *philo)
{
	t_time tmp;
	int		rest_time;

	gettimeofday(&tmp, NULL);
	rest_time = get_rest_time(philo);
	if (action == TAKING_FORK)
	{
		printf("%d [%d] taken forks <%d>\n", cur_time(philo), philo->id, rest_time);
		// printf("now status: %d %d %d %d\n", philo->info->fork[1].status, philo->info->fork[2].status, philo->info->fork[3].status, philo->info->fork[4].status);
	}
	else if (action == EATING)
		printf("%d [%d] is eating <%d> (rest num: %d)---------\n", cur_time(philo), philo->id, rest_time, philo->rest_num);
	else if (action == SLEEPING)
		printf("%d [%d] is sleeping <%d>\n", cur_time(philo), philo->id, rest_time);
	else if (action == THINKING)
		printf("%d [%d] is thinking <%d>\n", cur_time(philo), philo->id, rest_time);
	else if (action == DYING)
		printf("%d [%d] died <%d>\n", cur_time(philo), philo->id, rest_time);
	else if (action == READY_FORK)
		printf("%d [%d] is ready for forks!!\n", cur_time(philo), philo->id);
	else if (action == DONE_EAT)
		printf("%d [%d] finished eating\n", cur_time(philo), philo->id);
	else if (action == DONE_SLEEP)
		printf("%d [%d] finished sleeping\n", cur_time(philo), philo->id);
	else if (action == WAITING_FORK)
		printf("%d [%d] is waiting fork\n", cur_time(philo), philo->id);
	else
		printf("print_action error ! !\n");
}

void	status_monitoring(t_info *info, t_philo *philo)
{
	int	flag;
	t_time	cur;

	(void)philo;
	while (1)
	{
		// when someone died
		if (info->share_status == DEAD)
		{
			gettimeofday(&cur, NULL);
			printf("%d --- someone died ---\n", diff(info->start_time, cur));
			return ;
		}
		// usleep(100); // 함수 끝으로 보내면 share status 변경 확인을 늦게 함.....

		// when everyone ate min
		if (info->argu[MIN_TO_EAT] == -1)
			continue ;
		flag = 0;
		for (int i = 1; i <= info->argu[NUMBER_OF_PHILOS]; i++)
		{
			if (philo[i].rest_num > 0) // 다 안먹은사람
				flag = 1;
		}
		if (flag == 0)
		{
			gettimeofday(&cur, NULL);
			printf("%d --- everyone lived ---\n", diff(info->start_time, cur));
			return ;
		}
	}
}
