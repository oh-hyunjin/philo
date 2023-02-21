/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 11:50:35 by hyoh              #+#    #+#             */
/*   Updated: 2023/02/21 10:41:41 by hyoh             ###   ########.fr       */
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
#define READY_FORK 5
#define WAITING_FORK 6
#define DONE_EAT 7
#define DONE_SLEEP 8
#define USLEEP 9

// fork status
#define UNLOCK 0
#define LOCK 1

// share philo status
#define READY 0
#define ALIVE -1
#define DEAD -2

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
void	print_action(int action, t_philo *philo);
int		get_rest_time(t_philo *philo);
void	status_monitoring(t_info *info, t_philo *philo);
int		ft_usleep(t_philo *philo, long long wait);
unsigned int diff(t_time old, t_time new);
int cur_time(t_philo *philo);

// before routine
int	argv_check(int argc, char **argv, int argu[5]);
int	ft_atoi(char *str);
int	init_vars(t_info *info, t_philo **philo, pthread_t **pthread);
