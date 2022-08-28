/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merkol <merkol@42kocaeli.com.tr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 00:30:38 by merkol            #+#    #+#             */
/*   Updated: 2022/08/29 00:30:39 by merkol           ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eat(t_philo *ph)
{
	sem_wait(ph->attr->sem_forks);
	print_msg(ph, "has taken a fork");
	sem_wait(ph->attr->sem_forks);
	print_msg(ph, "has taken a fork");
	print_msg(ph, "is eating");
	ph->last_eat = cur_timestamp(0);
	my_sleep(ph->attr->eat_time);
	ph->c_eat++;
	sem_post(ph->attr->sem_forks);
	sem_post(ph->attr->sem_forks);
}

void	slp(t_philo *ph)
{
	print_msg(ph, "is sleeping");
	my_sleep(ph->attr->sleep_time);
}

void	thnk(t_philo *ph)
{
	print_msg(ph, "is thinking");
}
