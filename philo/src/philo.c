/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merkol <merkol@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 01:02:22 by merkol            #+#    #+#             */
/*   Updated: 2022/08/29 10:39:40 by merkol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thnk(t_philo *ph)
{
	if (ph->attr->anyone_die)
		return ;
	print_msg(ph, "is thinking");
}

void	eat(t_philo *ph)
{
	pthread_mutex_lock(&ph->attr->forks[ph->left]);
	print_msg(ph, "has taken a fork");
	if (ph->attr->ph_n == 1)
	{
		my_sleep(ph->attr->die_time + 10);
		return ;
	}
	pthread_mutex_lock(&ph->attr->forks[ph->right]);
	print_msg(ph, "has taken a fork");
	ph->last_eat = cur_timestamp(0);
	print_msg(ph, "is eating");
	my_sleep(ph->attr->eat_time);
	ph->c_eat++;
	pthread_mutex_unlock(&ph->attr->forks[ph->left]);
	pthread_mutex_unlock(&ph->attr->forks[ph->right]);
}

void	slp(t_philo *ph)
{
	if (ph->attr->anyone_die)
		return ;
	print_msg(ph, "is sleeping");
	my_sleep(ph->attr->sleep_time);
}

void	*routine(void *philo)
{
	t_philo	*ph;
	t_attr	*attr;

	ph = (t_philo *)philo;
	attr = ph->attr;
	if (ph->tid % 2 == 1)
		usleep(15000);
	while (!attr->anyone_die)
	{
		eat(ph);
		if (ph->c_eat == attr->opt_n || attr->breaker)
			break ;
		if (attr->anyone_die)
			break ;
		slp(ph);
		thnk(ph);
	}
	return (0);
}
