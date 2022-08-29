/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merkol <merkol@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 00:30:46 by merkol            #+#    #+#             */
/*   Updated: 2022/08/29 10:37:18 by merkol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_all(char **av, int ac, t_attr *attr)
{
	if (!init_attr(av, ac, attr))
		return (0);
	if (!init_semaphore(attr))
		return (2);
	init_philo(attr);
	return (1);
}

int	init_attr(char **av, int ac, t_attr *attr)
{
	if (!ft_atoi(av[1]) || !ft_atoi(av[2]) || !ft_atoi(av[3]) \
		|| !ft_atoi(av[4]))
		return (0);
	attr->ph_n = ft_atoi(av[1]);
	attr->die_time = ft_atoi(av[2]);
	attr->eat_time = ft_atoi(av[3]);
	attr->sleep_time = ft_atoi(av[4]);
	attr->opt_n = -1;
	attr->anyone_die = 0;
	if (ac == 6 && !ft_atoi(av[5]))
		return (0);
	else if (ac == 6 && ft_atoi(av[5]))
		attr->opt_n = ft_atoi(av[5]);
	return (1);
}

int	init_philo(t_attr *attr)
{
	int		i;

	i = -1;
	attr->philo = (t_philo *)malloc(sizeof(t_philo) * attr->ph_n);
	while (++i < attr->ph_n)
	{
		attr->philo[i].id = i;
		attr->philo[i].c_eat = 0;
		attr->philo[i].last_eat = cur_timestamp(0);
		attr->philo[i].attr = attr;
	}
	return (1);
}

int	init_semaphore(t_attr *attr)
{
	sem_unlink("./philo_forks");
	sem_unlink("./philo_writer");
	attr->sem_forks = sem_open("./philo_forks", O_CREAT, S_IRWXU, attr->ph_n);
	attr->sem_writer = sem_open("./philo_writer", O_CREAT, S_IRWXU, 1);
	if (attr->sem_forks == SEM_FAILED || attr->sem_writer == SEM_FAILED)
		return (0);
	return (1);
}
