/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjeunet <tjeunet@student.42barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 12:07:06 by tjeunet           #+#    #+#             */
/*   Updated: 2023/09/01 12:07:06 by tjeunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>


# define TAKING_FORK "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DEAD "died"
# define THREAD_ERROR "Error creating thread"
# define MALLOC_ERROR "Error allocating memory"
# define MUTEX_ERROR "Error creating mutex"


struct	s_data;

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		t1;
	int				id;
	int				eat_counter;
	int				is_eating;
	u_int64_t		time_left_before_death;
	pthread_mutex_t	lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}	t_philo;

typedef struct s_data
{
	pthread_t		*tid;
	int				philos_nb;
	int				meals_nb;
	int				philo_is_dead;
	int				philos_done_eating;		
	t_philo			*philos;
	u_int64_t		time_to_die;
	u_int64_t		time_to_eat;
	u_int64_t		time_to_sleep;
	u_int64_t		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
}	t_data;

int check_input(char **argv, int argc);
int handle_error(char *msg, t_data *data); 
int is_digit(char c);
int initialize(char **argv, int argc, t_data *data);
int	init_data(int argc, char **argv, t_data *data);
void	destroy_mutex(t_data *data);
int only_one_philo(t_data *data);
void	ft_print(char *msg, t_philo *philo);
int	create_threads(t_data *data);
void	*monitor_global_state(void *data_pointer);
void	*monitor_local_state(void *philo_pointer);
void	*run_philo_and_meals_monitor(void *philo_pointer);
int allocation(t_data *data);
int init_philos(t_data *data);
int	init_forks(t_data *data);
void	take_forks(t_philo *philo);
void drop_forks(t_philo *philo);
void    eat(t_philo *philo);
u_int64_t get_time(void);
void free_resources(t_data *data);
int ft_strcmp(char *s1, char *s2);

#endif

