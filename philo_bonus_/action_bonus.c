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
	sem_wait(info->fork);
	sem_wait(info->fork);
	sem_wait(info->print);
	printf("%d [%d] has taken forks\n", get_cur_time(info), philo->id);
	sem_post(info->print);
}

void	eating(t_info *info, t_philo *philo)
{
	philo->time = get_cur_time(info);
	philo->rest_num--;
	if (philo->rest_num == 0)
		sem_post(info->full); //unlock
	sem_wait(info->print);
	printf("%d [%d] is eating-----------(rest:%d)\n", get_cur_time(info), philo->id, philo->rest_num);
	sem_post(info->print);
	ft_usleep(philo, info->argu[TIME_TO_EAT]);
	sem_post(info->fork);
	sem_post(info->fork);
}

void	sleeping(t_info *info, t_philo *philo)
{
	sem_wait(info->print);
	printf("%d [%d] is sleeping\n", get_cur_time(info), philo->id);
	sem_post(info->print);
	ft_usleep(philo, info->argu[TIME_TO_SLEEP]);
}

void	thinking(t_info *info, t_philo *philo)
{
	sem_wait(info->print);
	printf("%d [%d] is thinking\n", get_cur_time(info), philo->id);
	sem_post(info->print);
}
