#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>
# define RED
# define BLUE
# define GREEN
# define RESET

typedef struct	s_last_meal
{
	pthread_mutex_t	meal_protect;
	long			last_meal;
}				t_last_meal;

typedef struct	s_philo
{
	pthread_t		thread;
	int				id;
	t_last_meal		last_meal;
	long			meal_counter;
	struct s_global	*global;
}				t_philo;

typedef struct	s_input
{
	long	number_of_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	number_of_meals;
}				t_input;

typedef struct	s_death
{
	pthread_mutex_t death_protect;
	int				death_flag;
}				t_death;

typedef struct	s_global
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	ft_print;
	t_death			death;
	t_input			input;
	t_philo			*philo;
	pthread_t		death_monitor;
	struct timeval	start_time;
}				t_global;

int		parsing_input(int ac, char **av, t_input *input);
void	start_simulation(t_input input);
void	*philo_routine(void *input);
void	*death_tracker(void *input);
long	timestamps(t_global *global);
void	smart_sleep(t_global *global, long sleeping_time);
void	ft_print(t_philo *philo, char *message);
int		read_death(t_death death);
long	last_meal(t_global *global, int id, int flag);

#endif
