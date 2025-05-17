/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:37:17 by haiqbal           #+#    #+#             */
/*   Updated: 2025/05/17 17:45:22 by haiqbal          ###   ########.fr       */
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
			return (0);
		usleep(500);
	}
	return (1);
}

int	print_action(t_table *table, int id, int status)
{
	pthread_mutex_lock(&table->write_lock);
	if (status == DEAD)
		printf("%llu %d died", get_time() - table->start_time, id);
	if (dead_check(table))
		return(pthread_mutex_unlock(&table->write_lock), 0);
	if (!dead_check(table))
	{
		printf("%llu %d", get_time() - table->start_time, id);
		if (status == EAT)
			printf("is eating");
		else if (status == SLEEP)
			printf("is sleeping");
		else if (status == THINK)
			printf("is thinking");
		else if (status == FORK)
			printf("has taken a fork");
	}
	pthread_mutex_unlock(&table->write_lock);
	return (1);
}
