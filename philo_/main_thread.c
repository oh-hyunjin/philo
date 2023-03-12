/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 18:14:26 by hyoh              #+#    #+#             */
/*   Updated: 2023/03/12 22:14:39 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <string.h>
#include <errno.h>
void	kill_all(t_info *info, t_philo *philo, pthread_t *pthread)
{
	int	i;

	usleep(500);
	i = 0;
	while (++i <= info->argu[NUM_OF_PHILOS])
	{
		pthread_join(pthread[i], NULL);
		if (pthread_mutex_destroy(&(info->fork[i].mutex)) != 0)
			printf("fork destroy fail!!!!!\n");
		else
			printf("fork destroy success~~~~\n");
	}
	printf("-----detach all success-----\n");
	// free(info->fork); // 맞나..?
	// free(philo);
	// free(pthread);
	(void)philo;
}

void	status_monitoring(t_info *info, t_philo *philos)
{
	int	i;
	int	flag;

	while (1)
	{
		i = 0;
		flag = 1;
		while (++i <= info->argu[NUM_OF_PHILOS])
		{
			if (get_rest_time(&philos[i]) < 0)
			{
				info->share_status = DEAD;
				printf("%d [%d] died\n", get_cur_time(&philos[i]), philos[i].id);
				return ;
			}
			if (philos[i].rest_num > 0)
				flag = 0;
		}
		if (info->argu[MIN_TO_EAT] != -1 && flag == 1)
		{
			info->share_status = FULL;
			return ;
		}
		usleep(300);
	}
}

int	main(int argc, char **argv)
{
	t_info		info;
	t_philo		*philo;
	pthread_t	*pthread;
	int			i;

	if (argv_check(argc, argv, info.argu) == -1 || \
			init_vars(&info, &philo, &pthread) == -1)
	{
		printf("error\n");
		return (0); //exit?
	}
	i = 0;
	while (++i <= info.argu[NUM_OF_PHILOS])
		pthread_create(&pthread[i], NULL, routine, &philo[i]);
	while (info.share_status != info.argu[NUM_OF_PHILOS])
		continue ;
	info.share_status = ALIVE;
	gettimeofday(&info.start_time, NULL);
	usleep(300);
	status_monitoring(&info, philo);
	kill_all(&info, philo, pthread);
}
// system("leaks ./philo");
// ps -eLf | grep testsrv
