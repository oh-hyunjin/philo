/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 09:03:32 by hyoh              #+#    #+#             */
/*   Updated: 2023/02/24 13:16:58 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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


int	argv_check(int argc, char **argv, t_info *info)
{
	int	i;

	if (argc != 5 && argc != 6)
		return (-1);
	argv++;
	i = -1;
	while(++i < argc - 1)
	{
		if (argc == 5 && i == 5)
			break ;
		info->argu[i] = ft_atoi(argv[i]);
		if (info->argu[i] == -1)
			return (-1);
	}
	if (argc == 5)
		info->argu[MIN_TO_EAT] = -1;
	return (1);
}

int	init(t_info *info, t_philo **philo, pid_t **pids)
{
	int		i;
	t_time	start;

	sem_unlink("fork");
	info->fork = sem_open("fork", O_CREAT, S_IRWXU, info->argu[NUMBER_OF_PHILOS]); // o_flags?????????
	if (info->fork == SEM_FAILED)
		retuen (-1);
	*philo = (t_philo *)malloc \
		(sizeof(t_philo) * (info->argu[NUMBER_OF_PHILOS] + 1));
	*pids = (pid_t *)malloc \
		(sizeof(pid_t) * (info->argu[NUMBER_OF_PHILOS] + 1));
	if (*philo == NULL || *pids == NULL) // *?????????
		return (-1);
	info->share_status = READY;
	i = 0;
	while (++i <= info->argu[NUMBER_OF_PHILOS])
	{
		(*philo)[i].id = i;
		(*philo)[i].rest_num = info->argu[MIN_TO_EAT];
		pids[i] = fork(); // fail???
		if (pids[i] == 0)
			action(info, &(*philo)[i]); // 자식은 여기서 exit
	}
	gettimeofday(&start, NULL);
	info->start_time = start.tv_sec * 1000 + start.tv_usec / 1000;
	return (1);
}

long long	get_rest_time(t_info *info, t_philo *philo)
{
	return (info->argu)
}

long long	get_cur_time(t_info *info)
{
	//now-start
	t_time		now;
	long long	now_time;

	now_time = now.tv_sec * 1000 + now.tv_usec / 1000;
	return (now_time - info->start_time);
}
