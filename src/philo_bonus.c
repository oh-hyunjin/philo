/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 12:43:33 by hyoh              #+#    #+#             */
/*   Updated: 2023/02/24 13:09:02 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	is_dead(t_info *info, t_philo *philo)
{
	if (info->share_status != ALIVE)
		return (1);
	if (get_rest_time(philo) < 0)
	{
		info->share_status = DEAD;
		printf("%ld [%d] died\n", cur_time(info), philo->id);
		return (1);
	}
	return (0);
}

void	taking_fork(t_info *info, t_philo *philo)
{
	if (is_dead(info, philo) == 1)
		return ;
	printf("%ld [%d] has taken forks\n", cur_time(info), philo->id);
}

void	eating(t_info *info, t_philo *philo)
{
	if (is_dead(info, philo) == 1)
		return ;
	printf("%ld [%d] is eating\n", cur_time(info), philo->id);
	ft_usleep(info->argu[TIME_TO_EAT]);
}

void	sleeping(t_info *info, t_philo *philo)
{
	if (is_dead(info, philo) == 1)
		return ;
	printf("%ld [%d] is sleeping\n", cur_time(info), philo->id);
	ft_usleep(info->argu[TIME_TO_SLEEP]);
}

void	thinking(t_info *info, t_philo *philo)
{
	if (is_dead(info, philo) == 1)
		return ;
	printf("%ld [%d] is thinking\n", cur_time(info), philo->id);
}

void	action(t_info *info, t_philo *philo)
{
	while(info->share_status != READY)
		continue ;
	while (info->share_status == ALIVE)
	{
		getting_fork(info, philo);
		eating(info, philo);
		sleeping(info, philo);
		thinking(info, philo);
	}
	exit(0);
}

int status_moniotroing(t_info *info, t_philo *philos)
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
	pid_t	*pids;
	int		status;
	int		i;

	if (argv_check(argc, argv, &info) < 0 || init(&info, &philos, &pids) < 0)
	{
		// philo, pids free
		printf("error\n");
		return (0);
	}

	status_moniotring(info, philos);
	while (wait(&status) != -1)
		continue ;

	// free variables
	sem_close(info.fork);
	sem_unlink(info.fork);
}
