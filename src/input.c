/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjeunet <tjeunet@student.42barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 12:09:23 by tjeunet           #+#    #+#             */
/*   Updated: 2023/09/01 12:09:23 by tjeunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_input(argv)
{
    int i;
    int j;

    i = 1;
    while (argv[i])
    {
        j = 0;
        while (argv[i][j])
        {
            if (!is_digit(argv[i][j]))
                return (handle_error("Error: invalid input character (not a digit).", NULL);
            j++;
        }
        i++;
    }
    return (0);
}