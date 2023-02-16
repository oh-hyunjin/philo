/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 11:50:35 by hyoh              #+#    #+#             */
/*   Updated: 2023/02/16 09:48:25 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct timeval t_time; // norm????

#define NUMBER_OF_PHILOS 0
#define TIME_TO_DIE 1
#define TIME_TO_EAT 2
#define TIME_TO_SLEEP 3
#define MIN_TO_EAT 4

#define EATING 0
#define TAKING_FORK 1
#define SLEEPING 2
#define THINKING 3
#define DYING 4

// fork status
#define UNLOCK 0
#define LOCK 1
#define NOTEXIST 2

// share philo status
#define ALIVE 0
#define DEAD 1

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	int				status;
}	t_fork;

typedef struct s_info
{
	int		argu[5];
	int		share_status;
	t_time	start_time;
	t_fork	*fork; // array
}	t_info;

typedef struct s_philo // routine 넘길 구조체 배열
{
	int		id;
	int		rest_num;
	t_time	time;
	t_info	*info;
}	t_philo;

//time : start time, philo time, cur time


//philo


// utils
int		ft_atoi(char *str);
int		argv_check(int argc, char **argv, int argu[5]);
void	print_action(int action, t_philo *philo);
int		get_time_diff(t_philo *philo);
void	status_monitoring(t_info *info, t_philo *philo);
int		init_vars(t_info *info, t_philo **philo, pthread_t **pthread);
