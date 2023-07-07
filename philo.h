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

typedef struct s_list
{
	long				content;
	struct s_list		*next;
}	t_list;

typedef struct s_philo
{
	int		id;
	int		philo_num;
	int		die_time;
	int		eat_time;
	int		sleep_time;
	int		eat_count;
	int		must_eat_num;
	t_table	*table;
}	t_philo;

typdef struct	s_table
{
	int		num_philosopheres;
	t_philo	*philosopher;
	int		must_eat_num;
}	t_table;

#endif
