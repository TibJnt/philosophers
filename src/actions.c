/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjeunet <tjeunet@student.42barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 15:24:40 by tjeunet           #+#    #+#             */
/*   Updated: 2023/09/03 15:24:40 by tjeunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/philo.h"

void    ft_print(char *msg, t_philo *philo)
{
    u_int64_t time;

    pthread_mutex_lock(&philo->data->write);
    time = get_time() - philo->data->start_time;
    if (ft_strcmp(msg, DEAD) == 0 && philo->data->philo_is_dead == 0)
    {
        philo->data->philo_is_dead = 1;
        printf("%llu %d %s\n", time, philo->id, msg);
    }
    if (!philo->data->philo_is_dead)
        printf("%llu %d %s\n", time, philo->id, msg);
    pthread_mutex_unlock(&philo->data->write);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	ft_print(TAKING_FORK, philo);
	pthread_mutex_lock(philo->l_fork);
	ft_print(TAKING_FORK, philo);
}

void drop_forks(t_philo *philo)
{
    pthread_mutex_unlock(philo->r_fork);
    pthread_mutex_unlock(philo->l_fork);
    ft_print(SLEEPING, philo);
    usleep(philo->data->time_to_sleep * 1000);
}

void    eat(t_philo *philo)
{
    take_forks(philo);
    pthread_mutex_lock(&philo->lock);
    philo->is_eating = 1;
    philo->time_left_before_death = get_time() + philo->data->time_to_die;
    ft_print(EATING, philo);
    philo->eat_counter++;
    usleep(philo->data->time_to_eat * 1000);
    philo->is_eating = 0;
    pthread_mutex_unlock(&philo->lock);
    drop_forks(philo);
}

