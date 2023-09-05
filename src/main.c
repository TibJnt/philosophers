/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjeunet <tjeunet@student.42barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 12:05:51 by tjeunet           #+#    #+#             */
/*   Updated: 2023/09/01 12:05:51 by tjeunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/philo.h"


int main (int argc, char **argv)
{
    t_data data;

    if (argc < 5 || argc > 6)
		return (1);
    if (check_input(argv))
        return (1);
    if (initialize(argv, argc, &data))
        return (1);
    if (data.philo_num == 1)
		  return (only_one_philo(&data));
    if (create_threads(&data))
        return (1);
    return (0);
}