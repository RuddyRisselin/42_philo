/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrisseli <rrisseli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 09:05:11 by rrisseli          #+#    #+#             */
/*   Updated: 2024/04/05 16:52:10 by rrisseli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>

typedef struct s_philo
{
	long	index;
	long	fork_left;
	long	fork_right;
	
}	t_philo;

typedef struct s_data
{
	int				n_philo;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				time_philo_eat;
	pthread_t		*threads;
	pthread_mutex_t *mutex;
	pthread_mutex_t mutex_init_philo;
	long			i;
	t_philo			*philo;
}		t_data;

void	*routine(t_data *data);
void	philo(t_data *data);
void	parsing_init(t_data *data, int ac, char **av);
void	thread_mutex_init(t_data *data);

char	**ft_split(char *str, char separator);
int		ft_atoi(char *str);
int		tablen(char **tab);
void	free_matrix(char **av);

#endif