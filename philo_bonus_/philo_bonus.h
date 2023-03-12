/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 12:43:55 by hyoh              #+#    #+#             */
/*   Updated: 2023/03/12 18:26:17 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>

# include <errno.h>
# include <string.h>

# define NUM_OF_PHILOS 0
# define TIME_TO_DIE 1
# define TIME_TO_EAT 2
# define TIME_TO_SLEEP 3
# define MIN_TO_EAT 4

# define TAKING_FORK 0
# define EATING 1
# define SLEEPING 2
# define THINKING 3

# define ALIVE 0
# define DEAD 1
# define FULL 2
// # define FULL 2

typedef struct timeval t_time; // norm????

typedef struct s_info
{
	int			argu[5];
	sem_t		*full;
	sem_t		*print;
	int			status;
	long long	start_time;
	sem_t		*fork;
}	t_info;

typedef struct s_philo // routine 넘길 구조체 배열
{
	int			id;
	int			rest_num;
	long long	time;
	t_info		*info;
}	t_philo;


// philo_bonus
void		action(t_info *info, t_philo *philo);
void		*death_check_thr(void *param);
void		*full_monitoring_thr(void *param);

// action_bonus
void		taking_fork(t_info *info, t_philo *philo);
void		eating(t_info *info, t_philo *philo);
void		sleeping(t_info *info, t_philo *philo);
void		thinking(t_info *info, t_philo *philo);

// ready_bonus
int			ft_atoi(char *str);
int			argv_check(int argc, char **argv, t_info *info);
int			init(t_info *info, t_philo **philo, int **pid);
int			sem_set(t_info *info);

// utils_bons
// int			is_dead(t_info *info, t_philo *philo);
int			get_cur_time(t_info *info);
int			get_rest_time(t_info *info, t_philo *philo);
int			ft_usleep(t_philo *philo, int wait);


#endif