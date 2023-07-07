/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikayacio <ikayacio@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 11:15:18 by ikayacio          #+#    #+#             */
/*   Updated: 2023/06/23 11:16:34 by ikayacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo t_philo;
typedef struct s_table t_table;

typedef struct s_philo
{
	int				id;
	long			die_time;
	long			eat_time;
	long			sleep_time;
	int				eat_count;
	int				is_alive;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork
	t_table	*table;
}	t_philo;

typdef struct	s_table
{
	int		num_philos;
	t_philo	*philos;
	int		must_eat_num;
	int		has_dead;
	pthread_mutex_t	*forks;
	pthread_t	*threads;
}	t_table;

void    free_all(t_table *table);
void    init_table(t_table *table, int philo_num, int must_eat_num);
void    init_philos();
void    init_forks(t_table *table);
int ft_atoi(const char *str);
int arg_check(char **argv, int argc);
#endif
