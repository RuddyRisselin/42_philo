/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:39:16 by rrisseli          #+#    #+#             */
/*   Updated: 2024/05/14 22:17:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex[philo->fork_left]);
	print_msg("has taken a fork", philo);
	pthread_mutex_lock(&philo->data->mutex[philo->fork_right]);
	check_vitals(philo);
	if (check_variables(philo) == 1)
	{
		pthread_mutex_unlock(&philo->data->mutex[philo->fork_right]);
		pthread_mutex_unlock(&philo->data->mutex[philo->fork_left]);
		return (0);
	}
	print_msg("is eating", philo);
	philo->meal_count++;
	philo->time_last_meal = (get_time() - philo->params[START_DATE]) + philo->params[TT_EAT];
	usleep(philo->params[TT_EAT] * 1000);
	if (philo->meal_count == philo->params[MAX_MEALS])
		philo->hungry = 0;
	pthread_mutex_unlock(&philo->data->mutex[philo->fork_right]);
	pthread_mutex_unlock(&philo->data->mutex[philo->fork_left]);
	return (1);
}

void	*routine(t_philo *philo)
{
	philo->time_last_meal = 0;
	if (philo->params[N_PHILO] == 1)
	{
		print_msg("has taken a fork", philo);
		usleep(philo->params[TT_DIE] * 1000);
		print_msg("died", philo);
		return (0);
	}
	if (philo->index % 2 == 0)
		ft_swap_fork(&philo->fork_left, &philo->fork_right);
	while(1)
	{
		if (philo_eat(philo) == 0)
			return (0);
		print_msg("is sleeping", philo);
		usleep(philo->params[TT_SLEEP] * 1000);
		check_vitals(philo);
		if (check_variables(philo) == 1)
			return (0);
		print_msg("is thinking", philo);
	}
	return (0);
}

void	philo(t_data *data)
{
	unsigned int i;
	
	i = 0;
	data->i = 0;
	data->dead = 0;
	while (i < data->param[N_PHILO])
	{
		memset(&data->philo[i], 0, sizeof(t_philo));
		data->philo[i].data = data;
		data->philo[i].index = i;
		philo_init(&data->philo[i]);
		if (pthread_create(&data->threads[i], NULL, (void *(*)(void *))&routine, &data->philo[i]) != 0)
			return ;
		i++;
	}
	i = 0;
	while (i < data->param[N_PHILO])
	{
		pthread_join(data->threads[i], NULL);
		i++;
	}
}
