/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 20:08:03 by haiqbal           #+#    #+#             */
/*   Updated: 2025/05/07 18:00:16 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	fork_avail_check(t_philo *philo, int first, int second)
{
	int	fone;
	int	ftwo;
	
	pthread_mutex_lock(&philo->sh_info->fork_lock[first]);
	fone = philo->sh_info->forks[first];
	pthread_mutex_unlock(&philo->sh_info->fork_lock[first]);
	pthread_mutex_lock(&philo->sh_info->fork_lock[second]);
	ftwo = philo->sh_info->forks[second];
	pthread_mutex_unlock(&philo->sh_info->fork_lock[second]);
	if (fone != philo->sh_info->forks[first] || ftwo != philo->sh_info->forks[second])
	return (0);
	return (1);
}

void	unlock_forks(t_philo *philo, int first, int second)
{
	fork_assign(philo, &first, &second);
	pthread_mutex_unlock(&philo->sh_info->fork_lock[first]);
	pthread_mutex_unlock(&philo->sh_info->fork_lock[second]);
}

void	lock_forks(t_philo *philo, int first, int second)
{
	fork_assign(philo, &first, &second);
	pthread_mutex_lock(&philo->sh_info->fork_lock[first]);
	pthread_mutex_lock(&philo->sh_info->fork_lock[second]);
}

void	fork_assign(t_philo *philo, int *first, int *second)
{
	if (philo->left_fork < philo->right_fork)
	{
		*first = philo->left_fork;
		*second = philo->right_fork;
	}
	else
	{
		*first = philo->right_fork;
		*second = philo->left_fork;
	}
}
