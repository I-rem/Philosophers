/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikayacio <ikayacio@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:19:11 by ikayacio          #+#    #+#             */
/*   Updated: 2023/07/19 16:19:13 by ikayacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_timestamp(t_philo *philo)
{
	struct timeval	current_time;
	long			timestamp;

	gettimeofday(&current_time, NULL);
	timestamp = (current_time.tv_sec - philo->table->start_time.tv_sec) * 1000
		+ (current_time.tv_usec - philo->table->start_time.tv_usec) / 1000;
	return (timestamp);
}

void	print_log(t_philo *philo, char *message)
{
	pthread_mutex_lock(&philo->table->print_lock);
	if (!philo->table->has_dead)
	{
		printf("%ld %d %s\n", get_timestamp(philo), philo->id, message);
		if (message[0] == 'd') // !
		philo->table->has_dead=1; // !
	}
	pthread_mutex_unlock(&philo->table->print_lock);
}

void	print_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print_lock);
	if (!philo->table->has_dead)
	{
		printf("%ld %d died\n", get_timestamp(philo), philo->id);
		philo->is_alive = 0;
		philo->table->has_dead = 1;
	}
	pthread_mutex_unlock(&philo->table->print_lock);
}

int	ft_atoi(const char *str)
{
	long long	result;

	result = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		str++;
		if (result > 2147483647)
			return (-1);
	}
	if (*str != '\0')
		result = -1;
	return (result);
}

int	arg_check(char **argv, int argc)
{
	(void)argv;
	if (argc != 5 && argc != 6)
		return (0);
	return (1);
}
