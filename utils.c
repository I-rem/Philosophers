#include "philo.h"

int is_dead(t_philo *philo) {
  long current_time;

  current_time = get_timestamp(philo);
  if (current_time - philo->last_eat_time >= philo->die_time) {
    print_log(philo, "died");
    philo->table->has_dead = 1;
    philo->is_alive = 0;
    return (1);
  }
  return (0);
}
long get_timestamp(t_philo *philo) {
  struct timeval current_time;
  long start_time;
  long current_timestamp;

  gettimeofday(&current_time, NULL);
  start_time = philo->table->start_time.tv_sec * 1000 +
               philo->table->start_time.tv_usec / 1000;
  current_timestamp = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
  return (current_timestamp - start_time);
}

void print_log(t_philo *philo, char *s) {
  pthread_mutex_lock(&philo->table->print_lock);
  if (!philo->table->has_dead)
    printf("%ld %d %s\n", get_timestamp(philo), philo->id, s);
  pthread_mutex_unlock(&philo->table->print_lock);
}

void eat_2(t_philo *philo, pthread_mutex_t *first_fork, pthread_mutex_t *second_fork)
{
  pthread_mutex_lock(first_fork);
  if(is_dead(philo))
  {
    pthread_mutex_unlock(first_fork);
    return ;
  }
  print_log(philo, "has taken a fork");
  if (first_fork != second_fork)
    {
        pthread_mutex_lock(second_fork);
        if(is_dead(philo))
        {
          pthread_mutex_unlock(second_fork);
          return ;
        }
        print_log(philo, "has taken a fork");
        print_log(philo, "is eating");
        philo->eat_count++;
        philo->last_eat_time = get_timestamp(philo);
        philo_sleep(2, philo);
        pthread_mutex_unlock(second_fork);
    }
    else
        usleep(philo->die_time*1000);
    pthread_mutex_unlock(first_fork);
}

void eat(t_philo *philo, int type)
{
  pthread_mutex_t *first_fork;
  pthread_mutex_t *second_fork;

  if (type == 1)
  {
    first_fork = philo->left_fork;
    second_fork = philo->right_fork;
  }
  else
  {
    first_fork = philo->right_fork;
    second_fork = philo->left_fork;
  }
  eat_2(philo, first_fork, second_fork);
}
