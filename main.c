/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 09:04:40 by rrisseli          #+#    #+#             */
/*   Updated: 2024/05/14 22:20:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// ./philo 4 310 200 100 le philo dois mourrir avec 310ms mm probleme que celui du dessu
void	free_all(t_data *data)
{
	unsigned int	i;

	i = 0;
	while(i < data->param[N_PHILO])
	{
		pthread_mutex_destroy(&data->mutex[i]);
		i++;
	}
	free(data->mutex);
	free(data->threads);
	free(data->philo);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5 || ac > 6)
	{
		printf("Error\n");
		return (1);
	}
	parsing_init(&data, ac, av);
	thread_mutex_init(&data);
	philo(&data);
	free_all(&data);
}
