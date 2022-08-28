/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merkol <merkol@42kocaeli.com.tr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 01:02:12 by merkol            #+#    #+#             */
/*   Updated: 2022/08/29 01:02:14 by merkol           ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	static t_attr	attr;
	int				i;

	i = -1;
	if (ac < 5 || ac >= 7)
		return (printf("Argüman Fazla veya Eksik!\n"));
	if (!init_all(av, ac, &attr))
		return (printf("Hatalı giriş!\n"));
	init_threads(&attr, &routine);
	while (++i < attr.ph_n)
		pthread_join(attr.philo[i].pth, NULL);
	while (--i >= 0)
		pthread_mutex_destroy(&attr.forks[i]);
	pthread_mutex_destroy(&attr.writer_mute);
	pthread_mutex_destroy(&attr.meal_mute);
	free(attr.forks);
	free(attr.philo);
	return (1);
}
