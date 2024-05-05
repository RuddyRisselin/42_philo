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

void	check_philo_died(t_philo *philo)
{
	if (philo->time_last_meal >= philo->data->time_to_die)
	{
		printf("\n\n--------the philo %ld die, end of simulation--------\n\n", philo->index);
		exit(0);
	}
	return ;
}