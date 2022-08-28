/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merkol <merkol@42kocaeli.com.tr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 00:30:25 by merkol            #+#    #+#             */
/*   Updated: 2022/08/29 00:30:26 by merkol           ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <fcntl.h>
# include <semaphore.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <unistd.h>

struct	s_attr;

typedef struct s_philo
{
	int					id;
	int					c_eat;
	long long			last_eat;
	pid_t				proc_id;
	struct s_attr		*attr;
}	t_philo;

typedef struct s_attr
{
	int					ph_n;
	int					die_time;
	int					eat_time;
	int					sleep_time;
	int					opt_n;
	int					anyone_die;
	long long			start_time;
	pthread_t			checker_th;
	sem_t				*sem_forks;
	sem_t				*sem_writer;
	sem_t				*meal_checker;
	t_philo				*philo;
}	t_attr;

void		take_fork(t_philo *ph);
int			init_all(char **av, int ac, t_attr *attr);
int			init_attr(char **av, int ac, t_attr *attr);
int			init_philo(t_attr *attr);
int			init_semaphore(t_attr *attr);
int			start_process(t_attr *attr);
int			ft_atoi(char *ptr);
long long	cur_timestamp(long long time);
void		my_sleep(long long time);
void		print_msg(t_philo *ph, char *msg);
void		eat(t_philo *ph);
void		slp(t_philo *ph);
void		thnk(t_philo *ph);
void		exit_cycle(t_attr *attr);
void		life_cycle(t_philo *ph);

#endif
