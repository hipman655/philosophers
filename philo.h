/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:57:34 by haiqbal           #+#    #+#             */
/*   Updated: 2025/04/14 16:29:57 by haiqbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>

typedef struct s_table
{
	unsigned long long	n_philo;
	unsigned long long	die_time;
	unsigned long long	eat_time;
	unsigned long long	sleep_time;
	long long			n_eat;
	int					*forks;
	t_philo				*philos;
	pthread_mutex_t		*fork_lock;
	pthread_mutex_t		*eat_lock;
	pthread_mutex_t		*death_lock;
}	t_table;

typedef struct s_philo
{
	int					id;
	unsigned long long	n_ate;
	unsigned long long	last_ate;
	pthread_t			thread;
	int					*dead;
	pthread_mutex_t		left_fork;
	pthread_mutex_t		right_fork;
}	t_philo;

//utils
long long	ft_atoll(const char *str);

#endif
