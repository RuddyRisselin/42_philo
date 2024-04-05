/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrisseli <rrisseli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 09:29:19 by rrisseli          #+#    #+#             */
/*   Updated: 2024/04/05 17:24:10 by rrisseli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_matrix(char **av)
{
	int	i;

	i = -1;
	if (av == NULL)
		return ;
	while (av[i])
		free(av[i++]);
	free(av - 1);
}

int	ft_atoi(char *str)
{
	int	res;
	int	negative;

	negative = 1;
	res = 0;
	while (*str && (*str == ' ' || *str == '\n' || *str == '\t'
			|| *str == '\v' || *str == '\f' || *str == '\r'))
		++str;
	if (*str == '-')
		negative = -1;
	if (*str == '-' || *str == '+')
		++str;
	while (*str && *str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - 48);
		++str;
	}
	if (res == 0)
	{
		printf("Error\n");
		exit(EXIT_FAILURE);
	}	
	return (res * negative);
}

void	parsing_init(t_data *data, int ac, char **av)
{
	bool	flag_ac_2;

	flag_ac_2 = false;
	if (ac == 2)
	{
		flag_ac_2 = true;
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

int	tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}
