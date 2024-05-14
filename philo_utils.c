/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 09:29:19 by rrisseli          #+#    #+#             */
/*   Updated: 2024/05/14 22:00:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int ft_atoi(char *str)
{
	unsigned int	res;

	res = 0;
	while (*str && (*str == ' ' || *str == '\n' || *str == '\t'
			|| *str == '\v' || *str == '\f' || *str == '\r'))
		++str;
	if (*str == '-')
	{
		printf("Error\n");
		exit (0);
	}
	if (*str == '+')
		++str;
	while (*str && *str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - 48);
		++str;
	}
	if ((res == 0) || (*str == '.' || *str == ',') || (res > 2147483647))
	{
		printf("Error\n");
		exit (0);
	}	
	return (res);
}

unsigned int	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, 0);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)dest;
	str2 = (unsigned char *)src;
	if (!n || dest == src)
		return (dest);
	while (n--)
		*str1++ = *str2++;
	return (dest);
}

void	ft_swap_fork(long *fork_left, long *fork_right)
{
	long tmp;

	tmp = *fork_left;  
	*fork_left = *fork_right;
	*fork_right = tmp;
}

void	print_msg(char *msg, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print);
	pthread_mutex_lock(&philo->data->check_dead);
	if (philo->data->dead == 0)
	{
		printf("%u %ld %s\n",(get_time() - philo->params[START_DATE]) , philo->index + 1, msg);
	}
	pthread_mutex_unlock(&philo->data->print);
	pthread_mutex_unlock(&philo->data->check_dead);
}
