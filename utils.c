/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:37:17 by haiqbal           #+#    #+#             */
/*   Updated: 2025/05/07 17:57:24 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_atoll(const char *str)
{
	long long	nb;
	int			i;

	nb = 0;
	i = 0;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	while (str[i])
		i++;
	if (i > 9)
		return (LLONG_MAX);
	while (*str >= '0' && *str <= '9')
	{
		nb = nb * 10 + *str - '0';
		str++;
	}
	return (nb);
}

unsigned long	get_time(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	my_usleep(unsigned long long time, t_philo *philo)
{
	const unsigned long long	start = get_time();

	while (get_time() < (start + time))
	{
		if (dead_check(philo->sh_info))
			return (1);
		usleep(500);
	}
	return (0);
}
