/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 11:50:35 by hyoh              #+#    #+#             */
/*   Updated: 2023/03/12 21:23:05 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>

# define NUM_OF_PHILOS 0
# define TIME_TO_DIE 1
# define TIME_TO_EAT 2
# define TIME_TO_SLEEP 3
# define MIN_TO_EAT 4

# define READY 0
# define ALIVE -1
# define DEAD -2
# define FULL -3

# define LOCK 0
# define UNLOCK 1

typedef struct timeval	t_time;
typedef pthread_mutex_t	t_print; // erase

typedef struct s_fork
{
	int				status;
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_info
{
	int		argu[5];
	int		share_status;
	t_time	start_time;
	t_fork	*fork;
	t_print	print;
}	t_info;

typedef struct s_philo // routine 넘길 구조체 배열
{
	int		id;
	int		rest_num;
	t_time	time;
	t_info	*info;
}	t_philo;

//main_thread.c
int		main(int argc, char **argv);
void	status_monitoring(t_info *info, t_philo *philos);
void	kill_all(t_info *info, t_philo *philo, pthread_t *pthread);

//philo
void	getting_fork(t_philo *philo, t_info *info, int *fst, int *snd);
void	eating(t_philo *philo, t_info *info);
void	sleeping(t_philo *philo, t_info *info);
void	thinking(t_philo *philo, t_info *info);
void	*routine(void *param);

// utils
int		get_rest_time(t_philo *philo);
int		ft_usleep(t_philo *philo, int wait);
int		diff(t_time old, t_time new);
int		get_cur_time(t_philo *philo);
void	free_arr(t_fork *fork, t_philo *philo, pthread_t *pthread);

// before routine
int		argv_check(int argc, char **argv, int argu[5]);
int		ft_atoi(char *str);
int		init_vars(t_info *info, t_philo **philo, pthread_t **pthread);

#endif