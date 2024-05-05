/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 09:05:11 by rrisseli          #+#    #+#             */
/*   Updated: 2024/05/05 19:22:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_data t_data;

typedef struct s_philo
{
	long	index;
	long	fork_left;
	long	fork_right;
	long	meal_count;
	bool	full;
	long	time_last_meal;
	t_data	*data;
	
}	t_philo;

typedef struct s_data
{
	int				n_philo;
	unsigned int				time_to_eat;
	unsigned int				time_to_sleep;
	unsigned int				time_to_die;
	unsigned int				time_philo_eat;
	size_t			start;
	size_t			end;
	pthread_t		*threads;
	pthread_mutex_t *mutex;
	pthread_mutex_t mutex_init_philo;
	long			i;
	t_philo			*philo;
	unsigned int	time_start;
	unsigned int	time_end;
	unsigned int	current_time;
}		t_data;

void			*routine(t_philo *philo);
void			philo(t_data *data);
void			parsing_init(t_data *data, int ac, char **av);
void			philo_init(t_philo *philo);
void			thread_mutex_init(t_data *data);

char			**ft_split(char *str, char separator);
int				ft_atoi(char *str);
int				tablen(char **tab);
void			free_matrix(char **av);
unsigned int	get_time(void);
void			check_philo_died(t_philo *philo);

#endif