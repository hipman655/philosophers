/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:48:30 by haiqbal           #+#    #+#             */
/*   Updated: 2025/05/25 10:19:20 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_args(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		if (!av[i][j])
			return (false);
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (ac != 5 && ac != 6)
		return (write(2, "Error: invalid number of arguments\n", 35), 1);
	if (!check_args(ac, av))
		return (write(2, "Error: invalid arguments\n", 25), 1);
	if (!initialisation(&table, ac, av))
		return (1);
	if (table.n_eat == 0)
		return (0);
	if (!threads_init(&table))
		return (1);
	return (0);
}
