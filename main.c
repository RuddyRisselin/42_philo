/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 09:04:40 by rrisseli          #+#    #+#             */
/*   Updated: 2024/05/05 19:07:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 1 || (ac == 2 && !av[1][0]) || ac > 6 || ac == 4 || ac == 3)
	{
		printf("Error\n");
		return (1);
	}
	parsing_init(&data, ac, av);
	thread_mutex_init(&data);
	philo(&data);
}
