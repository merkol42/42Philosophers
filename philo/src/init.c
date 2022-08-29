/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merkol <merkol@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 01:02:05 by merkol            #+#    #+#             */
/*   Updated: 2022/08/29 09:54:12 by merkol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_all(char **av, int ac, t_attr *attr)
{
	if (!init_attr(av, ac, attr))
		return (0);
	init_philo(attr);
	init_mutexes(attr);
	return (1);
}

int	init_attr(char **av, int ac, t_attr *attr)
{
	if (!ft_atoi(av[1]) || !ft_atoi(av[2]) || !ft_atoi(av[3]) \
		|| !ft_atoi(av[4]))
		return (0);
	attr->forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
	attr->ph_n = ft_atoi(av[1]);
	attr->die_time = ft_atoi(av[2]);
	attr->eat_time = ft_atoi(av[3]);
	attr->sleep_time = ft_atoi(av[4]);
	attr->opt_n = -1;
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
		attr->philo[i].tid = i;
		attr->philo[i].c_eat = 0;
		attr->philo[i].last_eat = cur_timestamp(0);
		attr->philo[i].right = i;
		attr->philo[i].left = (i + attr->ph_n - 1) % attr->ph_n;
		attr->philo[i].attr = attr;
	}
	return (1);
}

int	init_mutexes(t_attr *attr)
{
	int	i;

	i = -1;
	while (++i < attr->ph_n)
	{
		if (pthread_mutex_init(&attr->forks[i], NULL))
			return (0);
	}
	if (pthread_mutex_init(&attr->writer_mute, NULL))
		return (0);
	if (pthread_mutex_init(&attr->meal_mute, NULL))
		return (0);
	return (1);
}

int	init_threads(t_attr *attr, void *(*f)(void *))
{
	int			i;

	i = -1;
	attr->start_time = cur_timestamp(0);
	while (++i < attr->ph_n)
	{
		if (pthread_create(&attr->philo[i].pth, NULL, f, &attr->philo[i]))
			return (printf("Thread creating failed"));
	}
	checker(attr, attr->philo);
	return (0);
}
