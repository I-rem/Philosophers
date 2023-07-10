/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikayacio <ikayacio@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 11:14:59 by ikayacio          #+#    #+#             */
/*   Updated: 2023/06/23 11:15:12 by ikayacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    manager(t_philo *philo)
{
    long	die_time;
    int		has_eaten;
	long	current_time;
	long	time_since_last_eat;
	
    die_time = philo->die_time;
    has_eaten = 0;
    while (1) 
	{
        usleep(100);
        current_time = get_timestamp(philo);
        time_since_last_eat = current_time - philo->last_eat_time;
 	if (!(has_eaten) && time_since_last_eat > die_time) 
	{
        print_philo_died(philo);
        has_eaten = 1;
    }
        if (philo->is_alive &&  time_since_last_eat > die_time)
            print_death(philo);
        check_starve(philo, time_since_last_eat);
        if (!philo->is_alive)
            break;
    }
    return (NULL);

}

void    check_starve(t_philo *philo, long time_since_last_eat)
{
    int done_eating;

    if (philo->is_alive && time_since_last_eat > philo->die_time)
    {
        pthread_mutex_lock(&philo->table->finish_lock);
        done_eating = philo->table->done_eating;
        pthread_mutex_unlock(&philo->table->finish_lock);
        if(done_eating < philo->table->philo_num - 1)
            print_death(philo);
    }
}

void    check_must_eat_num(t_philo *philo, int must_eat_num)
{
    if (must_eat_num != -1 && philo->eat_count >= must_eat_num) //try to make this work with == must_eat_num 
    {
        int done_eating;
        pthread_mutex_lock(&philo->table->finish_lock);
        done_eating = philo->table-done_eating + 1;
        pthread_mutex_unlock(&philo->table->finish_lock);
    }
    if (done_eating == philo->table->philo_num)
    {
        pthread_mutex_lock(&philo->table->print_lock);
        if (!philo->table->has_dead)
            philo->table->has_dead = 1;
        pthread_mutex_unlock(&philo->table->print_lock);
    }
}

void    philo_sleep(t_philo *philo)
{
    print_message(philo, "is sleeping");
    usleep(philo->sleep_time * 1000);
    pthread_mutex_lock(&philo->eat_count_lock);
    philo->eat_count++;
    pthread_mutex_unlock(&philo->eat_count_lock);
}

long    get_timestamp(t_philo *philo)
{
    struct timeval  current_time;
    long    timestamp;

    gettimeofday(&current_time, NULL);
    timestamp = (current_time.tv_sec - philo->table->start_time.tv_sec) * 1000 +
                (current_time.tv_usec - philo->table->start_time.u_sec) / 1000;
    return (timestamp);
}

void    print_log(t_philo *philo, char *message)
{
    pthread_mutex_lock(&philo->table->print_lock);
    if (!philo->table->has_dead)
    {
        printf("%ld %d %s\n", get_timestamp(philo), philo->id, message);
        //if (message[0] == 'd')
        //    philo->table->has_dead=1;
    }
    pthread_mutex_unlock(&philo->table->print_lock);
}

void    print_death(t_philo *philo)
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

void    free_all(t_table *table)
{
    int i;

    i = -1;
    while (++i < table->philo_num)
         pthread_mutex_destroy(&table->forks[i]);
    pthread_mutex_destroy(&table->print_lock);
    pthread_mutex_destroy(&table->finish_lock);
    if(table->philos != NULL)
        free(table->philos);
     if (table->forks != NULL)
        free(table->forks);
    if (table->threads != NULL)
        free(table->threads);

}

void    init_table(t_table *table, int philo_num, int must_eat_num)
{
    table->philo_num = philo_num;
    table->must_eat_num = must_eat_num;
    table->has_dead = 0;
    table->done_eating = 0;
    gettimeofday(&table->start_time, NULL);
    table->philos = malloc(philo_num * sizeof(t_philo));
    table->forks = malloc(philo_num * sizeof(pthread_mutex_t));
    table->thread =malloc(philo_num * sizeof(pthread_t));
    pthread_mutex_init(&table->print_lock, NULL);
    pthread_mutex_init(&table->finish_lock, NULL);
    memset(table->philos, 0, philo_num * sizeof(t_philo));
}

void    init_philos(int die_time, int eat_time, int sleep_time)
{
    int i;

    i = 0;
    while(i < table->philo_num)
    {
        table->philos[i].id = i + 1;
        table->philos[i].die_time = die_time
        table->philos[i].eat_time = eat_time
        table->philos[i].sleep_time = sleep_time
        table->philos[i].eat_count = 0;
        table->philos[i].is_alive = 1;
        table->philos[i].table = table;
        table->philos[i].left_fork = &table->forks[i];
        table->philos[i].right_fork = &table->forks[(i + 1) % table->philo_num];
        pthread_mutex_init(&table->philos[i].eat_count_lock, NULL)
        i++;
    }
}

void    init_forks(t_table *table)
{
    int i;

    i = -1;
    while (++i < table->philo_num)
        pthread_mutex_init(&table->forks[i], NULL);
}

void    pick_forks(t_philo *philo)
{
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;

    left_fork = philo->left_fork;
    right_fork = philo->right_fork;
    if (philo->id % 2 == 0)
    {
        ptthread_mutex_lock(right_fork);
        ptthread_mutex_lock(left_fork);
    }
    else
    {
        ptthread_mutex_lock(left_fork);
        pthread_mutex_lock(right_fork);
    }
}


void    eat(t_philo *philo)
{
    pick_forks(philo);
    if (!philo->table->has_dead)
    {
        print_log(philo, "is eating");
        philo->last_eat_time = get_timestamp(philo);
        usleep(philo->time_to_eat * 1000);
    )
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}

void    start_routine(t_philo   *philo)
{
    pthread_t   manager_thread;

    pthread_create(&manager, NULL, manager, philo);
    pthread_detach(manager_thread);
    while (!philo->table->has_dead)
    {
        check_must_eat_num(philo, must_eat_num);
        eat(philo);
        philo_sleep(philo);
    }
    return(NULL);
}

int ft_atoi(const char *str)
{
    long long result;

    result = 0;
    while (*str == 32 || (*str >= 9 && *str <= 13))
        str++;
    if (*str == '+')
        str++;
    while (*str >= '0' && *str <= '9')
    {
        result = result * 10 + *str - 48;
        str++;
        if (result > 2147483647)
            result = -1;
    }
    return (result);
}

int arg_check(char **argv, int argc)
{
    int i;
    int j;

    if (argc < 5 || argc > 6)
        return (0);
    i = 0;
    while (argv[++i] != NULL)
    {
        j = -1;
        while (argv[i][++j] != '\0')
        {
            if (argv[i][j] == '+' && !(argv[i][j + 1] <= '9' && argv[i][j + 1] >= '0'))
                return (0);
            else if (argv[i][j] == '+' && (j != 0 && argv[i][j - 1] != ' '))
                return (0);
            else if (argv[i][j] != ' ' && argv[i][j] != '+' && (argv[i][j] < '0' || argv[i][j] > '9'))
                return (0);
        }
    }
    return (1);
}

int	main(int argc, char **argv)
{
	t_table	table;
	int		must_eat_num;
    int     i;

	must_eat_num = -1;
	if (!arg_check(argv, argc) || ft_atoi(argv[1]) == -1 || ft_atoi(argv[2]) == -1 || ft_atoi(argv[3]) == -1
		|| ft_atoi(argv[4]) || (argc == 6 && ft_atoi(argv[5]) == -1)) 
	{
        write(2, "Enter valid arguments!\n", 23);
        return (1);
    }
	if (argc == 6)
		must_eat_num = ft_atoi(argv[5]);
    init_table(&table, ft_atoi(argv[1]), must_eat_num);
    init_forks(&table);
    init_philos(&table,ft_atoi(argv[2]), ft_atoi(argv[3]), ft_atoi(argv[4]));
    i = -1;
    while(++i < table->philo_num)
        pthread_create(&table->threads, NULL, start_routine, &table->philos[i]);
    i = -1;
     while(++i < table->philo_num)
        pthread_join(table->threads, NULL);
    free_all(&table);
}
