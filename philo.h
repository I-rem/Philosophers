#ifndef PHILO_H
#define PHILO_H
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_philo t_philo;
typedef struct s_table t_table;

typedef struct s_philo {
  int id;
  long last_eat_time;
  int eat_count;
  int is_alive;
  int die_time;
  int eat_time;
  int sleep_time;
  t_table *table;
  pthread_mutex_t *left_fork;
  pthread_mutex_t *right_fork;
} t_philo;

typedef struct s_table {
  int num_philos;
  t_philo *philos;
  int must_eat_num;
  int has_dead;
  pthread_mutex_t *forks;
  pthread_mutex_t print_lock;
  pthread_mutex_t death_lock;
  pthread_t *threads;
  struct timeval start_time;
} t_table;

void init_table(t_table *table, int philo_num, int must_eat_num);
void init_philos(t_table *table, int die_time, int eat_time, int sleep_time);
void init_forks(t_table *table);
long get_timestamp(t_philo *philo);
void print_log(t_philo *philo, char *s);
void eat(t_philo *philo, int type);
int is_dead(t_philo *philo);
void philo_sleep(int type, t_philo *philo);
#endif
