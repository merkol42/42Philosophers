/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merkol <merkol@42kocaeli.com.tr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 01:07:30 by merkol            #+#    #+#             */
/*   Updated: 2022/08/29 01:07:31 by merkol           ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdint.h>

typedef struct s_philo	t_philo;

typedef struct s_attr
{
	int				ph_n;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				opt_n;
	int				count_full;
	int				breaker;
	int				anyone_die;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	writer_mute;
	pthread_mutex_t	meal_mute;
	t_philo			*philo;
}	t_attr;

typedef struct s_philo
{
	int				tid;
	int				meals;
	int				left;
	int				right;
	int				c_eat;
	long long		last_eat;
	pthread_t		pth;
	t_attr			*attr;
}	t_philo;

// init
int			init_all(char **av, int ac, t_attr *attr);
int			init_attr(char **av, int ac, t_attr *attr);
int			init_philo(t_attr *attr);
int			init_mutexes(t_attr *attr);
int			init_threads(t_attr *attr, void *(*f)(void *));

// life cycle
void		*routine(void *ph);
void		*checker(t_attr *atr, t_philo *ph);

// utils
int			ft_atoi(char *ptr);
long long	cur_timestamp(long long time);
void		my_sleep(long long time);
void		print_msg(t_philo *ph, char *msg);

#endif
