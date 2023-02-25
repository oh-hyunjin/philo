/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ready_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 11:50:58 by hyoh              #+#    #+#             */
/*   Updated: 2023/02/25 12:02:37 by hyoh             ###   ########.fr       */
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

int	init(t_info *info, t_philo **philo)
{
	int		i;
	pid_t	pid;

	sem_unlink("fork");
	info->fork = sem_open("fork", O_CREAT, S_IRWXU, info->argu[NUMBER_OF_PHILOS]); // o_flags?????????
	if (info->fork == SEM_FAILED)
		return (-1);
	*philo = (t_philo *)malloc \
		(sizeof(t_philo) * (info->argu[NUMBER_OF_PHILOS] + 1));
	if (*philo == NULL)
	{
		// free philo
		return (-1);
	}
	info->share_status = READY;
	i = 0;
	while (++i <= info->argu[NUMBER_OF_PHILOS])
	{
		(*philo)[i].id = i;
		(*philo)[i].rest_num = info->argu[MIN_TO_EAT];
		pid = fork();
		if (pid < 0)
			printf("fork fail\n");
		if (pid == 0)
			printf("	[%d] process created\n", i);
		if (pid != 0)
			action(info, &(*philo)[i]); // 자식은 여기서 exit
	}
	return (1);
}
