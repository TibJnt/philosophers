/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjeunet <tjeunet@student.42barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:15:20 by tjeunet           #+#    #+#             */
/*   Updated: 2023/09/04 12:15:20 by tjeunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/philo.h"

u_int64_t get_time(void)
{
    struct timeval tv;

    if (gettimeofday(&tv, NULL))
    {
        printf("Error getting time\n");
        return (0);
    }
    return ((u_int64_t)(tv.tv_sec * 1000) + (u_int64_t)(tv.tv_usec / 1000));
}

