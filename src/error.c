/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjeunet <tjeunet@student.42barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 12:32:50 by tjeunet           #+#    #+#             */
/*   Updated: 2023/09/01 12:32:50 by tjeunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/philo.h"

int handle_error(char *msg, t_data *data)
{
    if (data)
    {
        destroy_mutex(data);
        free_resources(data);
    }
    printf("%s\n", msg);
    return (1);
}


void    destroy_mutex(t_data *data)
{
    int i;

    i = 0;
    while (i < data->philos_nb)
    {
        pthread_mutex_destroy(&data->forks[i]);
        pthread_mutex_destroy(&data->philos[i].lock);
        i++;
    }
    pthread_mutex_destroy(&data->write);
    pthread_mutex_destroy(&data->lock);
}


void free_resources(t_data *data)
{
    if (data->tid)
    {
        free(data->tid);
        data->tid = NULL;
    }
    if (data->philos)
    {
        free(data->philos);
        data->philos = NULL;
    }
    if (data->forks)
    {
        free(data->forks);
        data->forks = NULL;
    }
}
