#ifndef PHILO_H
# define PHILO_H
#include <bits/types/struct_timeval.h>
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <limits.h>
# include <stddef.h>

typedef struct	s_death
{
	pthread_mutex_t	end_of_simulation;
	int				is_dead;
}				t_death;

typedef struct	s_last_meal
{
	pthread_mutex_t	meal_mutex;
	long			last_meal;
}				t_last_meal;

typedef struct	s_input
{
	int	number_of_philo;
	int	time_to_die;
	int	time_to_sleep;
	int	time_to_eat;
	int	number_of_meals;
}				t_input;

typedef struct	s_philo
{
	t_last_meal		last_meal;
	int				id;
	pthread_t		thread;
	struct s_global	*global;
}				t_philo;

typedef struct	s_global
{
	t_input			input;
	t_philo			*philo;
	pthread_mutex_t	*fork;
	t_death			is_dead;
	struct timeval	start_sim;
	pthread_t		supervisor;
}				t_global;

void	error_message(void);
int		input_parser(int ac, char **av, t_global *global);
void	start_simulation(t_global *global);
int		check_input(char **s, int ac);
void	fill_stack(char **s, int ac, t_global *global);
void	*philo_routine(void *input);
int		create_philos(t_global *global);
long	timestamp(t_global *global);
void	*death_checker(void *input);
void	ft_sleep(long time, t_global *global);
int		read_death(t_global *global);
long	last_meal(t_global *global, int i, int flag);

#endif
