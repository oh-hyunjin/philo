/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 12:13:03 by hyoh              #+#    #+#             */
/*   Updated: 2023/02/25 12:17:59 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	taking_fork(t_info *info, t_philo *philo)
{
	if (is_dead(info, philo) == 1)
		return ;
	sem_wait(info->fork);
	printf("%lld [%d] has taken forks\n", get_cur_time(info), philo->id);
}

void	eating(t_info *info, t_philo *philo)
{
	if (is_dead(info, philo) == 1)
		return ;
	philo->time = get_cur_time(info);
	printf("%lld [%d] is eating\n", get_cur_time(info), philo->id);
	ft_usleep(info, philo, info->argu[TIME_TO_EAT]);
	sem_post(info->fork);
}

void	sleeping(t_info *info, t_philo *philo)
{
	if (is_dead(info, philo) == 1)
		return ;
	printf("%lld [%d] is sleeping\n", get_cur_time(info), philo->id);
	ft_usleep(info, philo, info->argu[TIME_TO_SLEEP]);
}

void	thinking(t_info *info, t_philo *philo)
{
	if (is_dead(info, philo) == 1)
		return ;
	printf("%lld [%d] is thinking\n", get_cur_time(info), philo->id);
}
