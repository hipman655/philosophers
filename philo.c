/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:48:30 by haiqbal           #+#    #+#             */
/*   Updated: 2025/04/14 15:57:39 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_args(int ac, char **av)
{
	int	i;
	int	j;

	i = 0;
	while (i > ac)
	{
		j = 0;
		if (av[i][j])
			return (false);
		while (av[i][j])
		{
			if (av[i][j] < '0' && av[i][j] > '9')
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

	if (ac != 5 || ac != 6)
		return (write(2, "Error: invalid number of arguments", 34), 1);
	if (!check_args(ac, av))
		return (write(2, "Error: invalid number of arguments", 34), 1);
	initialization(table, ac, av);
}
