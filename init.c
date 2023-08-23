#include "philo.h"

void init_table(t_table *table, int philo_num, int must_eat_num)
{
  table->num_philos = philo_num;
  table->must_eat_num = must_eat_num;
  table->has_dead = 0;
  gettimeofday(&table->start_time, NULL);
  table->philos = malloc(philo_num * sizeof(t_philo));
  table->forks = malloc(philo_num * sizeof(pthread_mutex_t));
  table->threads = malloc(philo_num * sizeof(pthread_t));
  pthread_mutex_init(&table->print_lock, NULL);
  pthread_mutex_init(&table->death_lock, NULL);
  memset(table->philos, 0, philo_num * sizeof(t_philo));
}

void init_philos(t_table *table, int die_time, int eat_time, int sleep_time)
{
  int i;

  i = 0;
  while (i < table->num_philos)
  {
    table->philos[i].id = i + 1;
    table->philos[i].die_time = die_time;
    table->philos[i].eat_time = eat_time;
    table->philos[i].sleep_time = sleep_time;
    table->philos[i].last_eat_time = 0;
    table->philos[i].eat_count = 0;
    table->philos[i].is_alive = 1;
    table->philos[i].table = table;
    table->philos[i].left_fork = &table->forks[i];
    table->philos[i].right_fork = &table->forks[(i + 1) % table->num_philos];
    pthread_mutex_init(&table->philos[i].eat_count_lock, NULL);
    pthread_mutex_init(&table->philos[i].eat_lock, NULL);
    i++;
  }
}

void init_forks(t_table *table) {
  int i;

  i = -1;
  while (++i < table->num_philos)
    pthread_mutex_init(&table->forks[i], NULL);
}

void  philo_sleep(int type, t_philo *philo)
{
  if (type == 1)
  {
    print_log(philo, "is sleeping");
    if (philo->sleep_time >= philo->die_time)
      usleep(1000*(philo->die_time));
    else
      usleep(philo->sleep_time * 1000);
  }
  else
  {
    if (philo->eat_time >= philo->die_time)
      usleep(1000*(philo->die_time));
    else
      usleep(philo->eat_time * 1000);
  }
}
