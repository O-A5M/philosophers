#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

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
	long			last_meal;
	int				id;
	pthread_t		thread;
	struct s_global	*global;
}				t_philo;

typedef struct	s_global
{
	t_input			input;
	t_philo			*philo;
	pthread_mutex_t	*fork;
	pthread_mutex_t	end_of_simulation;
}				t_global;

void	error_message(void);
int		input_parser(int ac, char **av, t_global *global);
void	start_simulation(t_global *global);

#endif
