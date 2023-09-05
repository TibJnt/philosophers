/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjeunet <tjeunet@student.42barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 11:05:29 by tjeunet           #+#    #+#             */
/*   Updated: 2023/09/03 11:05:29 by tjeunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../lib/philo.h"

int init_data(int argc, char **argv, t_data *data)
{
    data->philos_nb = atoi(argv[1]);
    if (data->philos_nb == 0)
	    return (handle_error("Error: invalid number of philosophers.\n", NULL));
    data->time_to_die = (u_int64_t) atoi(argv[2]);
    data->time_to_eat = (u_int64_t) atoi(argv[3]);
    data->time_to_sleep = (u_int64_t) atoi(argv[4]);
    if (argc == 6)
        data->meals_nb = atoi(argv[5]);
    else
        data->meals_nb = -1;
    data->philo_is_dead = 0;
    data->philos_done_eating = 0;
    pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->lock, NULL);
	return (0);
}

int allocation(t_data *data)
{
    data->tid = malloc(sizeof(pthread_t) * data->philos_nb);
    if (!data->tid)
        return (handle_error(MALLOC_ERROR, data));
    data->philos = malloc(sizeof(t_philo) * data->philos_nb);
    if (!data->philos)
        return (handle_error(MALLOC_ERROR, data));
    data->forks = malloc(sizeof(pthread_mutex_t) * data->philos_nb);
    if (!data->forks)
        return (handle_error(MALLOC_ERROR, data));
    return (0);
}

int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (handle_error(MUTEX_ERROR, data));
		data->philos[i].l_fork = &data->forks[i];
		data->philos[i].r_fork = &data->forks[(i - 1 + data->philo_num) % data->philo_num];
		i++;
	}
	return (0);
}

int init_philos(t_data *data)
{
    int i;

    i = 0;
    while (i < data->philos_nb)
    {
        data->philos[i].id = i + 1;
        data->philos[i].data = data;
        data->philos[i].eat_counter = 0;
        data->philos[i].is_eating = 0;
        data->philos[i].time_left_before_death = data->time_to_die;
        if(pthread_mutex_init(&data->philos[i].lock, NULL))
            return (handle_error(MUTEX_ERROR, data));
        i++;
    }
}

int initialize(char **argv, int argc, t_data *data)
{
    if  (init_data(argc, argv, data))
        return (1);
    if (allocation(data))
        return (1);
    if (init_forks(data))
        return (1);
    init_philos(data);
    return (0);
}