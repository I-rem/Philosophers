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
	int		must_eat_num;
}	t_philo;

t_list	*ft_lstnew(long content);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
void	ft_lstclear(t_list **lst);
#endif
