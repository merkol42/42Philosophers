/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merkol <merkol@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 00:31:05 by merkol            #+#    #+#             */
/*   Updated: 2022/08/29 10:39:19 by merkol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	exit_cycle(t_attr *attr)
{
	int	i;
	int	ret;

	i = 0;
	while (i < attr->ph_n)
	{
		waitpid(-1, &ret, 0);
		if (ret != 0)
		{
			i = -1;
			while (++i < attr->ph_n)
				kill(attr->philo[i].proc_id, 15);
			break ;
		}
		i++;
	}
	sem_close(attr->sem_forks);
	sem_close(attr->sem_writer);
	sem_unlink("./philo_forks");
	sem_unlink("./philo_write");
}

void	*checkert(void *philo)
{
	t_attr	*attr;
	t_philo	*ph;

	ph = (t_philo *)philo;
	attr = ph->attr;
	while (1)
	{
		if (cur_timestamp(ph->last_eat) > attr->die_time)
		{
			print_msg(ph, "is died");
			attr->anyone_die = 1;
			sem_wait(attr->sem_writer);
			exit(1);
		}
		usleep(200);
		if (ph->c_eat == attr->opt_n)
			break ;
	}
	return (0);
}

void	life_cycle(t_philo *ph)
{
	ph->last_eat = cur_timestamp(0);
	pthread_create(&ph->attr->checker_th, NULL, checkert, ph);
	if (ph->id % 2)
		usleep(15000);
	while (!ph->attr->anyone_die)
	{
		eat(ph);
		if (ph->c_eat == ph->attr->opt_n)
			break ;
		slp(ph);
		thnk(ph);
	}
	pthread_join(ph->attr->checker_th, NULL);
	exit(EXIT_SUCCESS);
}

int	start_process(t_attr *attr)
{
	int		i;
	t_philo	*ph;

	i = -1;
	ph = attr->philo;
	attr->start_time = cur_timestamp(0);
	while (++i < attr->ph_n)
	{
		ph[i].proc_id = fork();
		if (ph[i].proc_id < 0)
			return (0);
		if (ph[i].proc_id == 0)
			life_cycle(&ph[i]);
		usleep(100);
	}
	exit_cycle(ph->attr);
	return (1);
}
