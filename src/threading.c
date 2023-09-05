/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjeunet <tjeunet@student.42barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 14:50:57 by tjeunet           #+#    #+#             */
/*   Updated: 2023/09/03 14:50:57 by tjeunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int only_one_philo(t_data *data)
{
    data->start_time = get_time();
	if (pthread_create(&data->tid[0], NULL, &run_philo_and_meals_monitor, &data->philos[0]))
		return (handle_error(THREAD_ERROR, data));
	pthread_detach(data->tid[0]);
	while (data->philo_is_dead == 0)
		usleep(0);
    destroy_mutex(data);
    free_resources(data);
	return (0);
}

void *monitor_global_state(void *data_pointer)
{
    t_data *data;

    data = (t_data *) data_pointer;
    while (data->philo_is_dead == 0)
    {
        if (data->philos_done_eating >= data->philos_nb)
        {
            pthread_mutex_lock(&data->lock);
            data->philo_is_dead = 1;
            pthread_mutex_unlock(&data->lock);
        }
    }
    return ((void *)0);
}

void *monitor_local_state(void *philo_pointer)
{
    t_philo	*philo;

    philo = (t_philo *) philo_pointer;
    while (philo->data->philo_is_dead == 0)
    {
        pthread_mutex_lock(&philo->lock);
        if (get_time() > philo->time_left_before_death && philo->is_eating == 0)
            ft_print(DEAD, philo);
        if (philo->eat_counter == philo->data->meals_nb)
        {
            pthread_mutex_lock(&philo->data->lock);
            philo->data->philos_done_eating++;
            pthread_mutex_unlock(&philo->data->lock);
        }
        pthread_mutex_unlock(&philo->lock);
    }
    return ((void *)0);
}

void  *run_philo_and_meals_monitor(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *) philo_pointer;
	philo->time_left_before_death = philo->data->time_to_die + get_time();
	if (pthread_create(&philo->t1, NULL, &monitor_local_state, (void *)philo))
		return ((void *)1);
	while (philo->data->philo_is_dead == 0)
	{
		eat(philo);
		ft_print(THINKING, philo);
	}
	if (pthread_join(philo->t1, NULL))
		return ((void *)1);
	return ((void *)0);
}

int create_threads(t_data *data)
{
    int	i;
    pthread_t t_global;

    i = -1;
    data->start_time = get_time();
    if (data->meals_nb > 0)
    {
        if (pthread_create(&t_global, NULL, &monitor_global_state, data))
            return (handle_error(THREAD_ERROR, data));
    }
    while (++i < data->philos_nb)
    {
        if (pthread_create(&data->tid[i], NULL, &run_philo_and_meals_monitor, &data->philos[i]))
            return (handle_error(THREAD_ERROR, data));
        usleep(1000);
    }
    i = -1;
    while (++i < data->philos_nb)
        if (pthread_join(data->tid[i], NULL))
            return (handle_error(THREAD_ERROR, data));
    return (0);
}

