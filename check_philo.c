/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 15:01:13 by marvin            #+#    #+#             */
/*   Updated: 2024/05/05 15:01:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_variables(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->check_dead);
	if ((philo->data->dead == 1) || (philo->hungry == 0))
	{
		pthread_mutex_unlock(&philo->data->check_dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->check_dead);
	return (0);
}

void	check_vitals(t_philo *philo)
{
	if (((get_time() - philo->params[START_DATE]) - philo->time_last_meal) > philo->params[TT_DIE])
	{
		print_msg("died", philo);
		pthread_mutex_lock(&philo->data->check_dead);
		philo->data->dead = 1;
		pthread_mutex_unlock(&philo->data->check_dead);
	}
	if (philo->meal_count >= philo->params[MAX_MEALS])
		philo->hungry = 0;
}
