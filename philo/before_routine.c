/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   before_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 10:52:14 by hyoh              #+#    #+#             */
/*   Updated: 2023/03/12 21:25:56 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_vars(t_info *info, t_philo **philo, pthread_t **pthread)
{
	int	i;
	int	philos_num;

	philos_num = info->argu[NUM_OF_PHILOS];
	info->fork = (t_fork *)malloc(sizeof(t_fork) * (philos_num + 1));
	*philo = (t_philo *)malloc(sizeof(t_philo) * (philos_num + 1));
	*pthread = (pthread_t *)malloc(sizeof(pthread_t) * (philos_num + 1));
	if (!info->fork || !philo || !pthread)
	{
		(free(fork), free(*philo), free(*pthread));
		return (-1);
	}
	pthread_mutex_init(&(info->print), NULL);
	info->share_status = READY;
	i = 0;
	while (++i <= philos_num)
	{
		pthread_mutex_init(&(info->fork[i].mutex), NULL);
		info->fork[i].status = UNLOCK;
		(*philo)[i].id = i;
		(*philo)[i].rest_num = info->argu[MIN_TO_EAT];
		(*philo)[i].info = info;
	}
	return (0);
}

int	ft_atoi(char *str)
{
	int	num;// unint?

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

int	argv_check(int argc, char **argv, int *argu)
{
	int	i;

	if (argc != 5 && argc != 6)
		return (-1);
	i = -1;
	while (++i < argc - 1)
	{
		argu[i] = ft_atoi(argv[i + 1]);
		if (argu[i] == -1)
			return (-1);
	}
	argu[MIN_TO_EAT] = -1;
	if (argc == 6)
	{
		argu[MIN_TO_EAT] = ft_atoi(argv[i]);
		if (argu[MIN_TO_EAT] == -1)
			return (-1);
	}
	return (0);
}
