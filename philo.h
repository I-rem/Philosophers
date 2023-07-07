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
	int		id;
	long		die_time;
	long		eat_time;
	long		sleep_time;
	int		eat_count;
	int		is_alive;
	t_table	*table;
}	t_philo;

typdef struct	s_table
{
	int		num_philos;
	t_philo	*philos;
	int		must_eat_num;
	int		has_dead;
}	t_table;

#endif
