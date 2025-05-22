/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:50:28 by haiqbal           #+#    #+#             */
/*   Updated: 2025/05/22 19:15:18 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eat_check(t_table *table)
{
	unsigned long long	i;

	i = 0;
	while (i < table->n_philo)
	{
		if (table->philos[i].n_ate < (unsigned long long)table->n_eat)
			return (0);
		i++;
	}
	return (1);
}

void	end_eat(t_table *table)
{
	pthread_mutex_lock(&table->death_lock);
	table->dead = true;
	pthread_mutex_unlock(&table->death_lock);
	pthread_mutex_unlock(&table->eat_lock);
}

void	philo_death(t_table *table, int i)
{
	pthread_mutex_lock(&table->death_lock);
	table->dead = true;
	pthread_mutex_unlock(&table->death_lock);
	print_action(table, table->philos[i].id, DEAD);
	pthread_mutex_unlock(&table->eat_lock);
}

void	*waiter_action(void *arg)
{
	unsigned long long	i;
	t_table				*table;

	table = (t_table *)arg;
	while (!dead_check(table))
	{
		i = 0;
		while (i < table->n_philo)
		{
			pthread_mutex_lock(&table->eat_lock);
			if (table->n_eat > 0 && eat_check(table))
			{
				end_eat(table);
				return (NULL);
			}
			if (get_time() > table->philos[i].last_ate + table->die_time)
			{
				philo_death(table, i);
				return (NULL);
			}
			pthread_mutex_unlock(&table->eat_lock);
			i++;
		}
	}
	return (NULL);
}
