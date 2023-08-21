#include "philo.h"
/*
void	*manager(void *v_philo)
{
	t_philo	*philo = v_philo;
	long	die_time;
	long	current_time;
	long	time_since_last_eat;

	die_time = philo->die_time;
	while (philo->is_alive)
	{
		current_time = get_timestamp(philo);
		time_since_last_eat = current_time - philo->last_eat_time;
		if (philo->is_alive && time_since_last_eat > die_time)
		{
			if (!philo->table->has_dead)
    		{
				print_log(philo, "died");
        		philo->table->has_dead = 1;
    		}
			philo->is_alive = 0;
			break ;
		}
	}
    // If there's only one philosopher and he is dead, exit the program.
	if (philo->table->num_philos == 1 && !philo->is_alive)
		free_all(philo->table);
	return (NULL);
}
*/
void	pick_forks(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (philo->id % 2 == 1)
	{  // If philosopher's id is odd, reverse fork order
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	else
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
	}
	pthread_mutex_lock(first_fork);
	print_log(philo, "has taken a fork");
	pthread_mutex_lock(second_fork);
	print_log(philo, "has taken a fork");
}

void	*start_routine(void *v_philo)
{
    t_philo *philo = v_philo;
    long    die_time;
    long    current_time;
    long    time_since_last_eat;

    die_time = philo->die_time;
    while (philo->is_alive)
    {
        current_time = get_timestamp(philo);
        time_since_last_eat = current_time - philo->last_eat_time;
        pthread_mutex_lock(&philo->eat_lock);
        if (time_since_last_eat > die_time)
            if (philo->is_alive)
            {
                print_log(philo, "died");
                philo->is_alive = 0;
                pthread_mutex_unlock(&philo->eat_lock);
                break;
            }
        pthread_mutex_unlock(&philo->eat_lock);
        eat(philo);
        print_log(philo, "is sleeping");
        usleep(philo->sleep_time * 1000);
        print_log(philo, "is thinking");
    }
    return (NULL);
}
}

void	check_must_eat_num(t_philo *philo, int must_eat_num)
{
	int	done_eating;
	int	i = -1;

	if (must_eat_num != -1 && philo->eat_count == must_eat_num)
	{
		pthread_mutex_lock(&philo->table->finish_lock);
		done_eating = ++philo->table->done_eating;
		pthread_mutex_unlock(&philo->table->finish_lock);
		if (done_eating == philo->table->num_philos)
		{
			pthread_mutex_lock(&philo->table->print_lock);
            if (!philo->table->has_dead)
                philo->table->has_dead = 1; // Ensure no further printing.
            pthread_mutex_unlock(&philo->table->print_lock);
            // Terminate all philosophers
            while (++i < philo->table->num_philos)
            	philo->table->philos[i].is_alive = 0;
        }
    }
}

int    main(int argc, char **argv)
{
    t_table	table;
    int		must_eat_num;
    int		i;

	must_eat_num = -1;
	if (!arg_check(argv, argc)    || ft_atoi(argv[1]) == -1 ||
        ft_atoi(argv[2]) == -1 || ft_atoi(argv[3]) == -1
        || ft_atoi(argv[4]) == -1 || (argc == 6 && ft_atoi(argv[5]) == -1))
    {
		write(2, "Enter valid arguments!\n", 23);
		return (1);
    }
	if (argc == 6)
		must_eat_num = ft_atoi(argv[5]);
	init_table(&table, ft_atoi(argv[1]), must_eat_num);
	init_forks(&table);
	init_philos(&table, ft_atoi(argv[2]), ft_atoi(argv[3]), ft_atoi(argv[4]));
	i = -1;
	while (++i < table.num_philos)
        pthread_create(&table.threads[i], NULL, start_routine, &table.philos[i]);
	i = -1;
	while (++i < table.num_philos)
        pthread_join(table.threads[i], NULL);
	free_all(&table);
    return (0);
}
