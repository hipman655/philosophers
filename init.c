/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:58:02 by haiqbal           #+#    #+#             */
/*   Updated: 2025/04/14 17:59:03 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int	init_table(t_table, table)

bool	initialisation(t_table	table, int ac, char **av)
{
	table.n_philo = ft_atoll(av[1]);
	table.die_time = ft_atoll(av[2]);
	table.eat_time = ft_atoll(av[3]);
	table.sleep_time = ft_atoll(av[4]);
	if (table.n_philo >= INT_MAX || table.eat_time >= INT_MAX
		|| table.die_time >= INT_MAX || table.sleep_time >= INT_MAX
		|| (ac == 6 && table.n_eat >= INT_MAX))
		return (printf("Error: Invalid arguments\n"), 1);
	if (ac == 6 && table.n_eat == 0)
		return (0);
	if (ac == 6)
		table.n_eat = ft_atoll(av[5]);
	table.forks = malloc(sizeof(int) * table.n_philo);
	if (!table.forks)
		return (printf("Error: Invalid arguments\n"), 1);
}
