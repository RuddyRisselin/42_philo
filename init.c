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

int	parsing_init(t_data *data, int ac, char **av)
{
	int (i) = 3;
	data->param[N_PHILO] = ft_atoi(av[1]);
	data->param[TT_DIE] = ft_atoi(av[2]);
	data->param[TT_EAT] = ft_atoi(av[3]);
	data->param[TT_SLEEP] = ft_atoi(av[4]);
	if (ac == 6)
	{
		data->param[MAX_MEALS] = ft_atoi(av[5]);
		i = 4;
	}
	else
		data->param[MAX_MEALS] = 10000;
	while (i >= 0)
	{
		if (data->param[i] == 0)
			return (printf("Error\n"), 1);
		i--;
	}
	data->param[START_DATE] = get_time();
	if (data->param[TT_SLEEP] > data->param[TT_DIE])
		data->param[TT_SLEEP] = data->param[TT_DIE];
	if (data->param[TT_EAT] > data->param[TT_DIE])
		data->param[TT_EAT] = data->param[TT_DIE];
	return (0);
}

void	thread_mutex_init(t_data *data)
{
	unsigned int	i;

	i = 0;
	data->threads = malloc(sizeof(pthread_t) * data->param[N_PHILO]);
	if (!data->threads)
		return ;
	data->mutex = malloc(sizeof(pthread_mutex_t) * data->param[N_PHILO]);
	if (!data->mutex)
		return (free(data->threads));
	data->philo = malloc(sizeof(t_philo) * data->param[N_PHILO]);
	if (!data->philo)
		return (free(data->mutex), free(data->threads));
	while (i < data->param[N_PHILO])
	{
		pthread_mutex_init(&data->mutex[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->check_dead, NULL);
	pthread_mutex_init(&data->print, NULL);
	return ;
}

void	philo_init(t_philo *philo)
{
	ft_memcpy(philo->params, philo->data->param, sizeof(t_params));
	philo->time_last_meal = 1;
	philo->fork_left = (philo->index + 1) % philo->params[N_PHILO];
	philo->fork_right = philo->index;
	philo->hungry = 1;
}
