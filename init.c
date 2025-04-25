/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanfas <hanfas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:58:02 by haiqbal           #+#    #+#             */
/*   Updated: 2025/04/24 17:31:06 by hanfas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	table_init(t_table *table, int ac, char **av)
{
	table->n_philo = ft_atoll(av[1]);
	table->die_time = ft_atoll(av[2]);
	table->eat_time = ft_atoll(av[3]);
	table->sleep_time = ft_atoll(av[4]);
	if (ac == 6)
		table->n_eat = ft_atoll(av[5]);
	if (table->n_philo >= INT_MAX || table->eat_time >= INT_MAX
		|| table->die_time >= INT_MAX || table->sleep_time >= INT_MAX
		|| (ac == 6 && table->n_eat >= INT_MAX))
		return (printf("Error: Invalid arguments\n"), false);
	if (ac == 6 && table->n_eat == 0)
		return (true);
	if (!forkies(table))
		return (false);
	table->philos = malloc(sizeof(t_philo) * table->n_philo);
	if (!table->philos)
		return (printf("Error: Malloc fail\n"), false);
	if (!mutex_init(table))
		return (false);
	table->start_time = get_time();
	return (true);
}

int	forkies(t_table	*table)
{
	unsigned long long	i;

	i = 0;
	table->forks = malloc(sizeof(int) * table->n_philo);
	if (!table->forks)
		return (printf("Error: Malloc fail\n"), 0);
	while (i < table->n_philo)
	{
		table->forks[i] = i;
		i++;
	}
	return (1);
}

int	mutex_init(t_table	*table)
{
	unsigned long long	i;

	i = 0;
	table->fork_lock = malloc(sizeof(pthread_mutex_t) * table->n_philo);
	if (!table->fork_lock)
		return (printf("Error: Malloc error\n"), 0);
	while (i < table->n_philo)
	{
		pthread_mutex_init(&table->fork_lock[i], NULL);
		i++;
	}
	pthread_mutex_init(&table->write_lock, NULL);
	pthread_mutex_init(&table->eat_lock, NULL);
	pthread_mutex_init(&table->death_lock, NULL);
	return (1);
}

bool	philos_init(t_table *table)
{
	unsigned long long	i;

	i = 0;
	while (i < table->n_philo)
	{
		table->philos[i].id = i + 1;
		table->philos[i].n_ate = 0;
		table->philos[i].last_ate = table->start_time;
		table->philos[i].dead = false;
		table->philos[i].left_fork = i;
		table->philos[i].right_fork = (i + 1) % table->n_philo;
		table->philos[i].sh_info = table;
		i++;
	}
	return (true);
}

bool	initialisation(t_table *table, int ac, char **av)
{
	if (!table_init(table, ac, av))
		return (false);
	if (!philos_init(table))
		return (false);
	return (true);
}
