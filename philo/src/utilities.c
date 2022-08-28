/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merkol <merkol@42kocaeli.com.tr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 01:02:31 by merkol            #+#    #+#             */
/*   Updated: 2022/08/29 01:02:33 by merkol           ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *ptr)
{
	long	number;
	int		delimiter;

	number = 0;
	delimiter = 0;
	if (*ptr == '-')
		return (0);
	if (*ptr == '+')
	{
		ptr++;
		delimiter++;
	}
	while (*ptr)
	{
		if (!(*ptr >= 48 && *ptr <= 57))
			return (0);
		number = number * 10 + (*(ptr++) - 48);
		delimiter++;
	}
	if (number == 0)
		return (0);
	if (number > 2147483647 || number < -2147483648 || delimiter > 11)
		return (0);
	return ((int)number);
}

long long	cur_timestamp(long long time)
{
	static struct timeval	te;
	long long				milliseconds;

	gettimeofday(&te, NULL);
	milliseconds = (te.tv_sec * 1000 + te.tv_usec / 1000) - time;
	return (milliseconds);
}

void	my_sleep(long long time)
{
	long long	now;

	now = cur_timestamp(0);
	while (cur_timestamp(0) - now < time)
		usleep(50);
}

void	print_msg(t_philo *ph, char *msg)
{
	pthread_mutex_lock(&ph->attr->writer_mute);
	if (!ph->attr->anyone_die)
	{
		printf("%lld %d %s\n", cur_timestamp(ph->attr->start_time), \
			ph->tid + 1, msg);
	}
	pthread_mutex_unlock(&ph->attr->writer_mute);
	return ;
}
