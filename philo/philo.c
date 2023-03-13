/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 11:17:50 by hyoh              #+#    #+#             */
/*   Updated: 2023/03/13 11:18:15 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo, t_info *info)
{
	int	fst;
	int	snd;

	getting_fork(philo, info, &fst, &snd);
	if (info->share_status != ALIVE)
		return ;
	philo->rest_num--;
	gettimeofday(&philo->time, NULL);
	printf("%d [%d] is eating ------\n", get_cur_time(philo), philo->id);
	if (philo->rest_num == 0) // ㅈㅣ우기
		printf("  %d satisfied must eat num~~~~~~~~~~~~~~~~~~~\n", philo->id);
	ft_usleep(philo, info->argu[TIME_TO_EAT]);
	if (philo->id % 2 == 1)
	{
		unlock_fork(&info->fork[fst]);
		unlock_fork(&info->fork[snd]);
	}
	else
	{
		unlock_fork(&info->fork[snd]);
		unlock_fork(&info->fork[fst]);
	}
}

void	sleeping(t_philo *philo, t_info *info)
{
	if (info->share_status != ALIVE)
		return ;
	printf("%d [%d] is sleeping\n", get_cur_time(philo), philo->id);
	ft_usleep(philo, info->argu[TIME_TO_SLEEP]);
}

void	thinking(t_philo *philo, t_info *info)
{
	if (info->share_status != ALIVE)
		return ;
	printf("%d [%d] is thinking\n", get_cur_time(philo), philo->id);
}

void	*routine(void *param)
{
	t_philo	*philo;
	t_info	*info;

	philo = (t_philo *)param;
	info = philo->info;
	info->share_status ++;
	while (info->share_status != ALIVE)
		continue ;
	gettimeofday(&philo->time, NULL);
	if (philo->id % 2 == 0)
		usleep(300);
	while (info->share_status == ALIVE)
	{
		eating(philo, philo->info);
		sleeping(philo, philo->info);
		thinking(philo, philo->info);
		usleep(400);
	}
	return (0);
}
