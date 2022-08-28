/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merkol <merkol@42kocaeli.com.tr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 01:01:57 by merkol            #+#    #+#             */
/*   Updated: 2022/08/29 01:02:00 by merkol           ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*checker(t_attr *atr, t_philo *ph)
{
	int	i;

	while (!atr->breaker)
	{
		i = -1;
		while (++i < atr->ph_n && !atr->anyone_die)
		{
			if (cur_timestamp(ph[i].last_eat) >= atr->die_time)
			{
				printf("%lld %d is died\n", cur_timestamp(atr->start_time), \
					ph[i].tid);
				atr->anyone_die = 1;
			}
			usleep(200);
		}
		if (atr->anyone_die)
			break ;
		i = -1;
		while (atr->opt_n > -1 && ++i < atr->ph_n && ph[i].c_eat == atr->opt_n)
			atr->count_full++;
		if (atr->count_full > atr->ph_n)
			atr->breaker = 1;
	}
	return (0);
}
