/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merkol <merkol@42kocaeli.com.tr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 00:30:56 by merkol            #+#    #+#             */
/*   Updated: 2022/08/29 00:30:58 by merkol           ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char **av)
{
	t_attr	attr;

	if (ac < 5 || ac >= 7)
		return (printf("Usage: tt_die tt_eat tt_sleep meal_count\n"));
	if (!init_all(av, ac, &attr))
		return (printf("Hatalı giriş!\n"));
	if (!start_process(&attr))
		return (printf("Fork oluşturulamadı!"));
	return (1);
}
