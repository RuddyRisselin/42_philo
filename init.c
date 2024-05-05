/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 22:36:39 by marvin            #+#    #+#             */
/*   Updated: 2024/05/04 22:36:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	parsing_init(t_data *data, int ac, char **av)
{
	data->start = get_time();
	printf("%ld\n", data->start);
	if (ac == 2)
	{
		av = ft_split(av[1], ' ');
	}
	data->n_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]) * 1000;
	data->time_to_eat = ft_atoi(av[3]) * 1000;
	data->time_to_sleep = ft_atoi(av[4]) * 1000;
	if (tablen(av) == 6)
		data->time_philo_eat = ft_atoi(av[5]) * 1000;
	else
		data->time_philo_eat = 0;
}

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
	if (data->i + 1 == data->n_philo)
		data->philo->fork_left = data->n_philo;
	else
		data->philo->fork_left = (data->i + 1) % data->n_philo;
	if ((data->i + 1) == 1)
		data->philo->fork_right = data->n_philo;
	else
		data->philo->fork_right = data->i;
	data->philo->full = false;
	//printf("philo[%ld] fork_left[%ld] fork right[%ld]\n", data->philo->index, data->philo->fork_left, data->philo->fork_right);
	pthread_mutex_unlock(&data->mutex_init_philo);
}
