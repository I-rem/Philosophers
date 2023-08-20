#include "philo.h"

void	check_starve(t_philo *philo, long time_since_last_eat)
{
	int	done_eating;

	if (philo->is_alive && time_since_last_eat > philo->die_time)
	{
		pthread_mutex_lock(&philo->table->finish_lock);
		done_eating = philo->table->done_eating;
		pthread_mutex_unlock(&philo->table->finish_lock);
		if (done_eating < philo->table->num_philos - 1)
		if (!philo->table->has_dead)
    {
		print_log(philo, "died");
        //printf("%ld %d died\n", get_timestamp(philo), philo->id);
        philo->table->has_dead = 1;
    }
	}
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
        pthread_mutex_init(&table->philos[i].eat_lock, NULL);
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

	philo->last_eat_time = get_timestamp(philo);
	print_log(philo, "is eating");
	usleep(philo->eat_time * 1000);
    pthread_mutex_unlock(philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);
    // Increase the eat count if eating was successful and philosopher is alive
     pthread_mutex_lock(&philo->eat_count_lock);
    if(philo->is_alive)
	{
        philo->eat_count++;
        check_must_eat_num(philo, philo->table->must_eat_num);
    }
    pthread_mutex_unlock(&philo->eat_count_lock);
}
