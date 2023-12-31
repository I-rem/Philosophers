# Philosophers
I never thought philosophy would be so deadly

## Overview
- One or more philosophers sit at a round table.
  There is a large bowl of spaghetti in the middle of the table.
- The philosophers alternatively eat, think, or sleep.
While they are eating, they are not thinking nor sleeping;
while thinking, they are not eating nor sleeping;
and, of course, while sleeping, they are not eating nor thinking.
- There are also forks on the table. There are as many forks as philosophers.
- Because serving and eating spaghetti with only one fork is very inconvenient, a
philosopher takes their right and their left forks to eat, one in each hand.
- When a philosopher has finished eating, they put their forks back on the table and
start sleeping. Once awake, they start thinking again. The simulation stops when
a philosopher dies of starvation.
- Every philosopher needs to eat and should never starve.
- Philosophers don’t speak with each other.
- Philosophers don’t know if another philosopher is about to die.
- No need to say that philosophers should avoid dying!
## Global Rules
You have to write a program for the mandatory part and another one for the bonus part
(if you decide to do the bonus part). They both have to comply with the following rules:
- Global variables are forbidden!
- Your(s) program(s) should take the following arguments:
number_of_philosophers time_to_die time_to_eat time_to_sleep
- [number_of_times_each_philosopher_must_eat]
number_of_philosophers: The number of philosophers and also the number
of forks.

◦ time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die
milliseconds since the beginning of their last meal or the beginning of the simulation, they die.

◦ time_to_eat (in milliseconds): The time it takes for a philosopher to eat.
During that time, they will need to hold two forks.

◦ time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.

◦ number_of_times_each_philosopher_must_eat (optional argument): If all
philosophers have eaten at least number_of_times_each_philosopher_must_eat
times, the simulation stops. If not specified, the simulation stops when a
philosopher dies.

- Each philosopher has a number ranging from 1 to number_of_philosophers.
- Philosopher number 1 sits next to philosopher number number_of_philosophers.
Any other philosopher number N sits between philosopher number N - 1 and philosopher number N + 1.
About the logs of your program:
- Any state change of a philosopher must be formatted as follows:
- timestamp_in_ms X has taken a fork
- timestamp_in_ms X is eating
- timestamp_in_ms X is sleeping
- timestamp_in_ms X is thinking
- timestamp_in_ms X died
Replace timestamp_in_ms with the current timestamp in milliseconds
and X with the philosopher number.
- A displayed state message should not be mixed up with another message.
- A message announcing a philosopher died should be displayed no more than 10 ms
after the actual death of the philosopher.
- Again, philosophers should avoid dying!
Your program must not have any data races.
Mandatory part

Program name: philo

Turn in files: Makefile, *.h, *.c, in directory philo/
Makefile: NAME, all, clean, fclean, re

Arguments 
number_of_philosophers 
time_to_die time_to_eat
time_to_sleep
[number_of_times_each_philosopher_must_eat]

**External functs**

memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock

**Description*:* Philosophers with threads and mutexes

The specific rules for the mandatory part are:
- Each philosopher should be a thread.
- There is one fork between each pair of philosophers. Therefore, if there are several
philosophers, each philosopher has a fork on their left side and a fork on their right
side. If there is only one philosopher, there should be only one fork on the table.
- To prevent philosophers from duplicating forks, you should protect the forks state
with a mutex for each of them.

# Evaluation
## Mandatory Part
### Error Handling
Follow the norm, make sure there are no memory leaks.
### Global Variables
Check if there is any global variable which is used to manage the shared resources among the philosophers
### philo code
Ensure the code of philo compiles with the following requierements and ask for explanations
- Check there is one thread per philosopher
- Check there is only one fork per philosopher
- Check if there is a mutex per fork and that it is used to check the for value and/or change it
- Check the outputs are never mixed up
- Check how the death of a philosopher is verified and if there is a mutex to prevent a philosopher from dying and starting eating at the same time
### philo testing
- Do not test with more than 200 philosophers
- Do not test with time_to_die or time_to_eat or time_to_sleep set to values lower than 60 ms
- Test 1 800 200 200. The philosopher shouldn't eat and die
- Test 5 800 200 200. No philosopher should die
- Test 5 800 200 200 7. No philosopher should die and simlation should stop after every philoopher has eaten at least 7 times
- Test 4 410 200 200. No philosopher should die
- Test 4 310 200 100. One pihlosopher should die
- Test with 2 philosophers and check the different times: a death delayed by more than 10 ms is unacceptable
- Test with any values of your choice to verify all the requierements. Ensure philosophers die at the rigt time, that they don't steal forks, and so forths.
