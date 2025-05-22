/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 15:38:29 by haiqbal           #+#    #+#             */
/*   Updated: 2025/05/18 18:27:34 by haiqbal          ###   ########.fr       */
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
	unlock_fork(philo, first, second);
	return (1);
}

int	sleep(t_philo *philo)
{
	if (!print_action(philo->sh_info, philo->id, SLEEP))
		return (0);
	if (!my_usleep(philo->sh_info->sleep_time, philo))
		return (0);
	return (1);
}

int think(t_philo *philo)
{
	if (!print_action(philo->sh_info, philo->id, THINK))
		return (0);
	return (1);
}
