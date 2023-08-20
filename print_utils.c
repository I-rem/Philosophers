#include "philo.h"

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

void	free_all(t_table *table)
{
	int	i;

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
