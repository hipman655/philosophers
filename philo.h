/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanfas <hanfas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:57:34 by haiqbal           #+#    #+#             */
/*   Updated: 2025/04/21 20:35:27 by hanfas           ###   ########.fr       */
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
# include <sys/time.h>

typedef struct s_philo	t_philo;

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
	pthread_mutex_t		write_lock;
	pthread_mutex_t		eat_lock;
	pthread_mutex_t		death_lock;
	pthread_t			monitor;
	ssize_t				start_time;
}	t_table;

typedef struct s_philo
{
	int					id;
	unsigned long long	n_ate;
	unsigned long long	last_ate;
	pthread_t			thread;
	bool				dead;
	int					left_fork;
	int					right_fork;
	t_table				sh_info;
}	t_philo;

//utilities
long long	ft_atoll(const char *str);

//initialisations
bool	initialisation(t_table table, int ac, char **av);
bool	table_init(t_table table, int ac, char **av);
bool	philos_init(t_table table);
int		forkies(t_table	table);
int		mutex_init(t_table	table);

#endif
