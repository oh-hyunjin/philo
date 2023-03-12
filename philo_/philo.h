/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 11:50:35 by hyoh              #+#    #+#             */
/*   Updated: 2023/02/24 09:10:06 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>

# define NUMBER_OF_PHILOS 0
# define TIME_TO_DIE 1
# define TIME_TO_EAT 2
# define TIME_TO_SLEEP 3
# define MIN_TO_EAT 4

typedef struct timeval t_time; // norm????
typedef pthread_mutex_t	m_fork;
typedef pthread_mutex_t	m_print;

typedef struct s_info
{
	int		argu[5];
	int		ready_philo_num;
	t_time	start_time;
	m_fork	*fork; // array
	m_print	print;
}	t_info;

typedef struct s_philo // routine 넘길 구조체 배열
{
	int		id;
	int		rest_num;
	t_time	time;
	t_info	*info;
}	t_philo;

//philo
int		getting_fork(t_philo *philo, t_info *info, int *fst, int *snd);
void	eating(t_philo *philo, t_info *info);
void	sleeping(t_philo *philo, t_info *info);
void	thinking(t_philo *philo, t_info *info);
void	*routine(void *param);

// utils
// void	print_action(int action, t_philo *philo);
int		get_rest_time(t_philo *philo);
int		ft_usleep(t_philo *philo, int wait);
int		diff(t_time old, t_time new);
int		get_cur_time(t_philo *philo);
void	status_monitoring(t_info *info, t_philo *philo);

// before routine
int		argv_check(int argc, char **argv, int argu[5]);
int		ft_atoi(char *str);
int		init_vars(t_info *info, t_philo **philo, pthread_t **pthread);

#endif