/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikayacio <ikayacio@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:19:02 by ikayacio          #+#    #+#             */
/*   Updated: 2023/07/19 16:19:04 by ikayacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleep(t_philo *philo)
{
	print_log(philo, "is sleeping");
	usleep(philo->sleep_time * 1000);
	pthread_mutex_lock(&philo->eat_count_lock);
	philo->eat_count++; // !
	pthread_mutex_unlock(&philo->eat_count_lock);
}

void	init_table(t_table *table, int philo_num, int must_eat_num)
{
	table->num_philos = philo_num;
	table->must_eat_num = must_eat_num;
	table->has_dead = 0;
	table->done_eating = 0;
	gettimeofday(&table->start_time, NULL);
	table->philos = malloc(philo_num * sizeof(t_philo));
	table->forks = malloc(philo_num * sizeof(pthread_mutex_t));
	table->threads = malloc(philo_num * sizeof(pthread_t));
	pthread_mutex_init(&table->print_lock, NULL);
	pthread_mutex_init(&table->finish_lock, NULL);
	memset(table->philos, 0, philo_num * sizeof(t_philo));
}

void	init_philos(t_table *table, int die_time, int eat_time, int sleep_time)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].die_time = die_time;
		table->philos[i].eat_time = eat_time;
		table->philos[i].sleep_time = sleep_time;
		table->philos[i].eat_count = 0;
		table->philos[i].is_alive = 1;
		table->philos[i].table = table;
		table->philos[i].left_fork = &table->forks[i];
		table->philos[i].right_fork = &table->forks[(i + 1)
			% table->num_philos];
		pthread_mutex_init(&table->philos[i].eat_count_lock, NULL);
		i++;
	}
}

void	init_forks(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->num_philos)
		pthread_mutex_init(&table->forks[i], NULL);
}


void	eat(t_philo *philo)
{
	pick_forks(philo);
	if (!philo->table->has_dead)
	{
		print_log(philo, "is eating");
		philo->eat_count += 1;
		philo->last_eat_time = get_timestamp(philo);
		usleep(philo->eat_time * 1000);

	}
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
