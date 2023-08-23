#include "philo.h"

void *start_routine(void *v_philo)
{
  t_philo *philo;

  philo = (t_philo *)v_philo;
  while (!philo->table->has_dead && !is_dead(philo)
  && !((philo->eat_count == philo->table->must_eat_num) && philo->table->must_eat_num != 0))
  {
    print_log(philo, "is thinking");
    if (philo->id % 2 == 1)
      eat(philo, 1);
    else
      eat(philo, 2);
    if(!philo->table->has_dead && !is_dead(philo)
  && !((philo->eat_count == philo->table->must_eat_num) && philo->table->must_eat_num != 0))
    philo_sleep(1, philo);
  }
  return (NULL);
}

void free_all(t_table *table) {
  int i;

  i = -1;
  while (++i < table->num_philos)
    pthread_mutex_destroy(&table->forks[i]);
  pthread_mutex_destroy(&table->print_lock);
  pthread_mutex_destroy(&table->death_lock);
  if (table->philos != NULL)
    free(table->philos);
  if (table->forks != NULL)
    free(table->forks);
  if (table->threads != NULL)
    free(table->threads);
}

int ft_atoi(const char *str) {
  long long result;

  result = 0;
  while (*str == ' ' || (*str >= 9 && *str <= 13))
    str++;
  if (*str == '+')
    str++;
  while (*str >= '0' && *str <= '9') {
    result = result * 10 + *str - '0';
    str++;
    if (result > 2147483647)
      return (-1);
  }
  if (*str != '\0')
    result = -1;
  return (result);
}

int arg_check(char **argv, int argc) {
  (void)argv;
  if (argc != 5 && argc != 6)
    return (0);
  return (1);
}

int main(int argc, char **argv) {
  t_table table;
  int must_eat_num;
  int i;

  must_eat_num = -1;
  if (!arg_check(argv, argc) || ft_atoi(argv[1]) == -1 ||
      ft_atoi(argv[2]) == -1 || ft_atoi(argv[3]) == -1 ||
      ft_atoi(argv[4]) == -1 || (argc == 6 && ft_atoi(argv[5]) == -1)) {
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
