/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrisseli <rrisseli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:39:16 by rrisseli          #+#    #+#             */
/*   Updated: 2024/04/05 17:34:00 by rrisseli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thread_mutex_init(t_data *data)
{
	int i;

	i = 0;
	data->threads = malloc(sizeof(pthread_t) * data->n_philo);
	if (!data->threads)
		exit (0);
	data->mutex = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	if (!data->mutex)
		exit(0);
	data->philo = malloc(sizeof(t_philo) * data->n_philo);
	if (!data->philo)
		exit(0);
	while(i < data->n_philo)
	{
		pthread_mutex_init(&data->mutex[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->mutex_init_philo, NULL);
	return ;
}

void	philo_init(t_data *data)
{
	pthread_mutex_lock(&data->mutex_init_philo);
	data->philo->index = data->i + 1;
	data->philo->fork_left = (data->i + 1) % data->n_philo;
	data->philo->fork_right = data->i;
	//printf("philo[%ld] fork_left[%ld] fork right[%ld]\n", data->philo->index, data->philo->fork_left, data->philo->fork_right);
	pthread_mutex_unlock(&data->mutex_init_philo);
}

void	*routine(t_data *data)
{
	philo_init(data);
	data->i++;
	if (data->i % 2 == 0)
	{
		pthread_mutex_lock(&data->mutex[data->philo->fork_left]);
		printf("timestamp_in_ms %ld has taken a fork\n", data->i);
		pthread_mutex_lock(&data->mutex[data->philo->fork_right]);
		printf("timestamp_in_ms %ld is eating\n", data->i);
		usleep(data->time_to_eat);
		pthread_mutex_unlock(&data->mutex[data->philo->fork_left]);
		pthread_mutex_unlock(&data->mutex[data->philo->fork_right]);
	}
	else
	{
		pthread_mutex_lock(&data->mutex[data->philo->fork_right]);
		printf("timestamp_in_ms %ld has taken a fork\n", data->i);
		pthread_mutex_lock(&data->mutex[data->philo->fork_left]);
		printf("timestamp_in_ms %ld is eating\n", data->i);
		usleep(data->time_to_eat);
		pthread_mutex_unlock(&data->mutex[data->philo->fork_right]);
		pthread_mutex_unlock(&data->mutex[data->philo->fork_left]);
	}
	
	return (NULL);
}

void	philo(t_data *data)
{
	int i;
	i = 0;
	data->i = 0;	
	thread_mutex_init(data);
	while (i < data->n_philo)
	{
		if (pthread_create(&data->threads[i], NULL, (void *(*)(void *))&routine, data))
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
