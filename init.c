/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:58:02 by haiqbal           #+#    #+#             */
/*   Updated: 2025/05/25 17:27:26 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	table_init(t_table *table, int ac, char **av)
{
	table->n_philo = ft_atoll(av[1]);
	table->die_time = ft_atoll(av[2]);
	table->eat_time = ft_atoll(av[3]);
	table->sleep_time = ft_atoll(av[4]);
	table->n_eat = -1;
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
		return (free(table->forks), printf("Error: Malloc fail\n"), false);
	if (!mutex_init(table))
		return (free_data(table, 0), false);
	table->start_time = get_time();
	if (table->start_time == -1)
		return (1);
	table->dead = false;
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
		if (i == 0 || i == table->n_philo - 1)
			table->forks[i] = table->n_philo;
		else if (i % 2 == 0)
			table->forks[i] = i + 2;
		else
			table->forks[i] = i + 1;
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
	if (ac == 6 && table->n_eat == 0)
		return (true);
	if (!philos_init(table))
		return (free_data(table, 0), false);
	return (true);
}
