/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:11:25 by haiqbal           #+#    #+#             */
/*   Updated: 2025/05/22 19:26:56 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eat(t_philo *philo)
{
	int	first;
	int	second;

	fork_assign(philo, &first, &second);
	if (!print_action(philo->sh_info, philo->id, FORK))
		return (0);
	if (!print_action(philo->sh_info, philo->id, FORK))
		return (0);
	if (!print_action(philo->sh_info, philo->id, EAT))
		return (0);
	if (!my_usleep(philo->sh_info->eat_time, philo))
		return (0);
	pthread_mutex_lock(&philo->sh_info->eat_lock);
	philo->n_ate += 1;
	philo->last_ate = get_time();
	pthread_mutex_unlock(&philo->sh_info->eat_lock);
	philo->sh_info->forks[philo->left_fork] = philo->id;
	philo->sh_info->forks[philo->right_fork] = philo->id;
	unlock_forks(philo, first, second);
	return (1);
}

int	slleep(t_philo *philo)
{
	if (!print_action(philo->sh_info, philo->id, SLEEP))
		return (0);
	if (!my_usleep(philo->sh_info->sleep_time, philo))
		return (0);
	return (1);
}

int	think(t_philo *philo)
{
	if (!print_action(philo->sh_info, philo->id, THINK))
		return (0);
	return (1);
}
