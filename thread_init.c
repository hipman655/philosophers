/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:11:13 by haiqbal           #+#    #+#             */
/*   Updated: 2025/05/22 19:33:17 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dead_check(t_table *sh_info)
{
	unsigned long long	i;

	i = 0;
	pthread_mutex_lock(&sh_info->death_lock);
	if (sh_info->dead == false)
		i = 0;
	else
		i = 1;
	pthread_mutex_unlock(&sh_info->death_lock);
	return (i);
}

void	kill_philo(t_philo *philo)
{
	my_usleep(philo->sh_info->die_time, philo);
	pthread_mutex_lock(&philo->sh_info->death_lock);
	philo->sh_info->dead = true;
	pthread_mutex_unlock(&philo->sh_info->death_lock);
}

void	*action(void *arg)
{
	t_philo	*philo;
	int		first;
	int		second;

	philo = (t_philo *)arg;
	if (philo->sh_info->n_philo == 1)
	{
		kill_philo(philo);
		return (NULL);
	}
	while (!dead_check(philo->sh_info))
	{
		fork_assign(philo, &first, &second);
		if (!fork_avail_check(philo, first, second))
		{
			lock_forks(philo, first, second);
			if (!eat(philo))
				return (unlock_forks(philo, first, second), NULL);
			if (!slleep(philo))
				return (NULL);
			if (!think(philo))
				return (NULL);
		}
	}
	return (NULL);
}

int	threads_init(t_table *table)
{
	unsigned long long int	i;

	i = 0;
	while (i < table->n_philo)
	{
		if (pthread_create(&table->philos[i].thread, NULL,
				&action, &table->philos[i]))
			return (printf("Error: pthread_create failed\n"), 1);
		i++;
	}
	if (table->n_philo > 1 && pthread_create(&table->waiter, NULL,
			&waiter_action, table))
		return (printf("Error: pthread_create failed\n"), 1);
	if (table->n_philo > 1 && pthread_join(table->waiter, NULL))
		return (printf("Error: pthread_join failed\n"), 1);
	i = 0;
	while (i < table->n_philo)
	{
		if (pthread_join(table->philos[i].thread, NULL))
			return (printf("Error: pthread_join failed\n"), 1);
		i++;
	}
	return (0);
}
