/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:11:33 by haiqbal           #+#    #+#             */
/*   Updated: 2025/05/18 18:35:42 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutex(t_table *table)
{
	unsigned long long	i;

	i = 0;
	while (i < table->n_philo)
	{
		pthread_mutex_destroy(&table->fork_lock[i]);
		i++;
	}
	pthread_mutex_destroy(&table->eat_lock);
	pthread_mutex_destroy(&table->write_lock);
	pthread_mutex_destroy(&table->death_lock);
}

void	free_data(t_table *table, int i)
{
	free(table->forks);
	free(table->philos);
	if (i == 1)
	{
		destroy_mutex(table);
		free(table->fork_lock);
	}
}