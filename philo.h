/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 09:05:11 by rrisseli          #+#    #+#             */
/*   Updated: 2024/07/08 22:21:07 by marvin           ###   ########.fr       */
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
# include <string.h>
# include <limits.h>

# define N_PHILO		0
# define TT_DIE			1
# define TT_EAT			2
# define TT_SLEEP		3
# define MAX_MEALS		4
# define START_DATE		5
# define PARAMS_SIZE	6

typedef struct s_data	t_data;
typedef unsigned int	t_params[6];

typedef struct s_philo
{
	long		index;
	long		fork_left;
	long		fork_right;
	long		meal_count;
	long		time_last_meal;
	int			hungry;
	t_data		*data;
	t_params	params;
}	t_philo;

typedef struct s_data
{
	unsigned int	current_time;
	long			i;
	int				dead;
	size_t			start;
	pthread_t		*threads;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	check_dead;
	pthread_mutex_t	print;
	t_philo			*philo;
	t_params		param;
}		t_data;

void			*routine(t_philo *philo);
void			philo(t_data *data);
int				philo_eat(t_philo *philo);
void			check_vitals(t_philo *philo);
int				check_variables(t_philo *philo);

void			thread_mutex_init(t_data *data);
void			parsing_init(t_data *data, int ac, char **av);
void			philo_init(t_philo *philo);
void			print_msg(char *msg, t_philo *philo);

unsigned int	ft_atoi(char *str);
int				tablen(char **tab);
unsigned int	get_time(void);
void			free_all(t_data *data);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			ft_swap_fork(long *fork_left, long *fork_right);
void			monitor(t_data *data);

#endif