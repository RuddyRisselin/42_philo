/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:39:16 by rrisseli          #+#    #+#             */
/*   Updated: 2024/05/05 19:42:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(t_philo *philo)
{
	t_data	*data;
	
	data = philo->data;
	data->i++;
	while(1)
	{
		check_philo_died(philo);
		if (philo->index % 2 == 0)																// si le philo est un nb pair il prend une fork puis l'autre, il mange et
		{																					// il lache les fourchette
				pthread_mutex_lock(&data->mutex[philo->fork_left]);
				printf("%lu %ld has taken a fork\n",(get_time() - data->start) , philo->index);
				pthread_mutex_lock(&data->mutex[philo->fork_right]);
				printf("%lu %ld is eating\n", (get_time() - data->start), philo->index);
				usleep(data->time_to_eat * 1000);
				philo->full = true;												// si le philo mange alors full = true
				philo->time_last_meal = get_time() - data->start;					// set l'horraire du dernier repas
				pthread_mutex_unlock(&data->mutex[philo->fork_right]);
				pthread_mutex_unlock(&data->mutex[philo->fork_left]);
				if (philo->full == true)
				{
					printf("%lu %ld is sleeping\n", (get_time() - data->start), philo->index);		// si il est full alors il dort pdt TIME_TO_SLEEP puis pense
					usleep(data->time_to_sleep * 1000);
				}
				printf("%lu %ld is thinking\n", (get_time() - data->start), philo->index);
		}
		else																				// same mais pour impaire
		{
				pthread_mutex_lock(&data->mutex[philo->fork_right]);
				printf("%lu %ld has taken a fork\n",(get_time() - data->start) , philo->index);
				pthread_mutex_lock(&data->mutex[philo->fork_left]);
				printf("%lu %ld is eating\n", (get_time() - data->start), philo->index);
				usleep(data->time_to_eat * 1000);
				philo->full = true;												// si le philo mange alors full = true
				philo->time_last_meal = get_time() - data->start;				// set l'horraire du dernier repas
				pthread_mutex_unlock(&data->mutex[philo->fork_right]);
				pthread_mutex_unlock(&data->mutex[philo->fork_left]);
				if (philo->full == true)
				{
					printf("%lu %ld is sleeping\n", (get_time() - data->start), philo->index);	// si il est full alors il dort pdt TIME_TO_SLEEP puis pense
					usleep(data->time_to_sleep * 1000);
				}
				printf("%lu %ld is thinking\n", (get_time() - data->start), philo->index);

		}
	}
	return (NULL);
}

void	philo(t_data *data)
{
	int i;
	i = 0;
	data->i = 0;
	while (data->i < data->n_philo) // init de chaque philo : id, fork_letft, fork_right, full, time_last_meal
	{
		data->philo[data->i].data = data;
		data->philo[data->i].index = data->i + 1;
		philo_init(&data->philo[data->i]);
		data->i++;
	}
	data->i = 0;
	while (i < data->n_philo)
	{
		if (pthread_create(&data->threads[i], NULL, (void *(*)(void *))&routine, &data->philo[i]) != 0)
			return ;
		i++;
	}
	i = 0;
	while (i < data->n_philo)
	{
		pthread_join(data->threads[i], NULL);
		i++;
	}
}
