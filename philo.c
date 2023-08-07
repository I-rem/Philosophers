#include "philo.h"

void    *manager(void *v_philo)
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
        if (philo->is_alive && time_since_last_eat > die_time)
        {
            print_death(philo);
            philo->is_alive = 0;
            break ;
        }
    }

    // If there's only one philosopher and he is dead, exit the program.
    if (philo->table->num_philos == 1 && !philo->is_alive) {
        free_all(philo->table);
        exit(0); // Exit the entire program
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
        if (done_eating < philo->table->num_philos - 1)
            print_death(philo);
    }
}

void    free_all(t_table *table)
{
    int    i;

    i = -1;
    while (++i < table->num_philos)
    {
        pthread_mutex_destroy(&table->forks[i]);
        pthread_mutex_destroy(&table->philos[i].eat_count_lock);
        pthread_mutex_destroy(&table->philos[i].eat_lock);
    }
    pthread_mutex_destroy(&table->print_lock);
    pthread_mutex_destroy(&table->finish_lock);

    if (table->philos != NULL)
        free(table->philos);
    if (table->forks != NULL)
        free(table->forks);
    if (table->threads != NULL)
        free(table->threads);
}


void    pick_forks(t_philo *philo)
{
    pthread_mutex_t    *left_fork;
    pthread_mutex_t    *right_fork;

    left_fork = philo->left_fork;
    right_fork = philo->right_fork;

    pthread_mutex_lock(left_fork);
    print_log(philo, "has taken a fork");
    pthread_mutex_lock(right_fork);
    print_log(philo, "has taken a fork");
}






void    *start_routine(void *v_philo)
{
    pthread_t    manager_thread;
    t_philo    *philo = v_philo;

    pthread_create(&manager_thread, NULL, manager, v_philo);
    pthread_detach(manager_thread);
    while (philo->is_alive)
    {
        check_must_eat_num(philo, philo->table->must_eat_num);
        if (philo->table->has_dead || !philo->is_alive)
            break;
        eat(philo);
        philo_sleep(philo);
        print_log(philo, "is thinking");
        if (philo->table->has_dead || !philo->is_alive)
            break;
    }
    return (NULL);
}




void    check_must_eat_num(t_philo *philo, int must_eat_num)
{
    int    done_eating;

    done_eating = 0;
    if (must_eat_num != -1 && philo->eat_count == must_eat_num)
    {
        pthread_mutex_lock(&philo->table->finish_lock);
        done_eating = ++philo->table->done_eating;
        pthread_mutex_unlock(&philo->table->finish_lock);
    }
    if (done_eating == philo->table->num_philos)
    {
        pthread_mutex_lock(&philo->table->print_lock);
        if (!philo->table->has_dead)
            philo->table->has_dead = 1;
        pthread_mutex_unlock(&philo->table->print_lock);
    }
}

int    main(int argc, char **argv)
{
    t_table    table;
    int        must_eat_num;
    int        i;

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

void    philo_sleep(t_philo *philo)
{
    print_log(philo, "is sleeping");
    usleep(philo->sleep_time * 1000);
}

void    init_table(t_table *table, int philo_num, int must_eat_num)
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

void    init_philos(t_table *table, int die_time, int eat_time, int sleep_time)
{
    int    i;

    i = 0;
    while (i < table->num_philos)
    {
        table->philos[i].id = i + 1;
        table->philos[i].die_time = die_time;
        table->philos[i].eat_time = eat_time;
        table->philos[i].sleep_time = sleep_time;
        table->philos[i].eat_count = 0;
        table->philos[i].is_alive = 1;
	pthread_mutex_init(&table->philos[i].eat_lock, NULL);
        table->philos[i].table = table;
        table->philos[i].left_fork = &table->forks[i];
        table->philos[i].right_fork = &table->forks[(i + 1)
            % table->num_philos];
        pthread_mutex_init(&table->philos[i].eat_count_lock, NULL);
        pthread_mutex_init(&table->philos[i].eat_lock, NULL);
        i++;
    }
}


void    init_forks(t_table *table)
{
    int    i;

    i = -1;
    while (++i < table->num_philos)
        pthread_mutex_init(&table->forks[i], NULL);
}

void    print_death(t_philo *philo)
{
    pthread_mutex_lock(&philo->table->print_lock);
    if (!philo->table->has_dead)
    {
        printf("%ld %d died\n", get_timestamp(philo), philo->id);
        philo->table->has_dead = 1;
    }
    pthread_mutex_unlock(&philo->table->print_lock);
}

long    get_timestamp(t_philo *philo)
{
    struct timeval    current_time;
    long              start_time;
    long              current_timestamp;

    gettimeofday(&current_time, NULL);
    start_time = philo->table->start_time.tv_sec * 1000 +
        philo->table->start_time.tv_usec / 1000;
    current_timestamp = current_time.tv_sec * 1000 +
        current_time.tv_usec / 1000;
    return (current_timestamp - start_time);
}

void    eat(t_philo *philo)
{
    pick_forks(philo);
    philo->last_eat_time = get_timestamp(philo);
    print_log(philo, "is eating");
    usleep(philo->eat_time * 1000);
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
    pthread_mutex_lock(&philo->eat_count_lock);
    philo->eat_count++;
    pthread_mutex_unlock(&philo->eat_count_lock);
}





void    print_log(t_philo *philo, char *msg)
{
    pthread_mutex_lock(&philo->table->print_lock);
    if (!philo->table->has_dead)
        printf("%ld %d %s\n", get_timestamp(philo), philo->id, msg);
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
