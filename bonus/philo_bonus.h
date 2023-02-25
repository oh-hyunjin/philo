/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 12:43:55 by hyoh              #+#    #+#             */
/*   Updated: 2023/02/25 12:18:16 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <semaphore.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>

# define NUMBER_OF_PHILOS 0
# define TIME_TO_DIE 1
# define TIME_TO_EAT 2
# define TIME_TO_SLEEP 3
# define MIN_TO_EAT 4

# define READY 0
# define ALIVE -1
# define DEAD -2
# define FULL -3

# define TAKING_FORK 0
# define EATING 1
# define SLEEPING 2
# define THINKING 3

typedef struct timeval t_time; // norm????

typedef struct s_info
{
	int			argu[5];
	int			share_status;
	long long	start_time;
	sem_t		*fork;
}	t_info;

typedef struct s_philo // routine 넘길 구조체 배열
{
	int			id;
	int			rest_num;
	long long	time;
}	t_philo;


// philo_bonus
void		status_monitoring(t_info *info, t_philo *philos);
void		action(t_info *info, t_philo *philo);

// action_bonus
void		taking_fork(t_info *info, t_philo *philo);
void		eating(t_info *info, t_philo *philo);
void		sleeping(t_info *info, t_philo *philo);
void		thinking(t_info *info, t_philo *philo);

// ready_bonus
int			ft_atoi(char *str);
int			argv_check(int argc, char **argv, t_info *info);
int			init(t_info *info, t_philo **philo);

// utils_bons
int			is_dead(t_info *info, t_philo *philo);
long long	get_cur_time(t_info *info);
long long	get_rest_time(t_info *info, t_philo *philo);
int			ft_usleep(t_info *info, t_philo *philo, int wait);


#endif