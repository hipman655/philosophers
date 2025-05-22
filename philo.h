/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haiqbal <haiqbal@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:57:34 by haiqbal           #+#    #+#             */
/*   Updated: 2025/05/19 18:36:04 by haiqbal          ###   ########.fr       */
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

# define EAT 0
# define SLEEP 1
# define THINK 2
# define FORK 3
# define DEAD 4

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
	bool				dead;
	pthread_t			waiter;
	ssize_t				start_time;
}	t_table;

typedef struct s_philo
{
	int					id;
	unsigned long long	n_ate;
	unsigned long long	last_ate;
	pthread_t			thread;
	int					left_fork;
	int					right_fork;
	t_table				*sh_info;
}	t_philo;

//utilities
long long		ft_atoll(const char *str);
unsigned long	get_time(void);
int				my_usleep(unsigned long long time, t_philo *philo);
int				print_action(t_table *table, int id, int status);

//initialisations
bool	initialisation(t_table *table, int ac, char **av);
bool	table_init(t_table *table, int ac, char **av);
bool	philos_init(t_table *table);
int		forkies(t_table	*table);
int		mutex_init(t_table	*table);

//memory free
void	free_data(t_table *table, int i);
void	destroy_mutex(t_table *table);

//fork utilities
void	fork_assign(t_philo *philo, int *first, int *second);
int		fork_avail_check(t_philo *philo, int first, int second);
void	lock_forks(t_philo *philo, int first, int second);
void	unlock_forks(t_philo *philo, int first, int second);

//thread initialisation
int		threads_init(t_table *table);
void	action(void *arg);
void	kill_philo(t_philo *philo);
int		dead_check(t_table *sh_info);

//philosopher actions
int	eat(t_philo *philo);
int	sleep(t_philo *philo);
int think(t_philo *philo);

//waiter functions
void	*waiter_action(void *arg);
int		eat_check(t_table *table);
void	end_eat(t_table *table);
void	philo_death(t_table *table, int i);

#endif
