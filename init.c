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
	if (ac == 2)
	{
		av = ft_split(av[1], ' ');
	}
	data->n_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (tablen(av) == 6)
		data->time_philo_eat = ft_atoi(av[5]);
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

void	philo_init(t_philo *philo)
{
	//philo->index = philo->data->i + 1;
	if (philo->index + 1 == philo->data->n_philo)
		philo->fork_left = philo->data->n_philo;
	else
		philo->fork_left = (philo->index + 1) % philo->data->n_philo;
	if ((philo->index + 1) == 1)
		philo->fork_right = philo->data->n_philo;
	else
		philo->fork_right = philo->index;
	philo->full = false;
	philo->time_last_meal = 0;
	printf("philo[%ld] fork_left[%ld] fork right[%ld]\n", philo->index, philo->fork_left, philo->fork_right);
}
