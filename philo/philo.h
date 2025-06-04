#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stddef.h>
# include <limits.h>

typedef struct	s_input
{
	int	num_of_philo;
	int	time_to_eat;
	int	time_to_sleep;
	int	time_to_die;
	int	num_of_eats;
}				t_input;

// typedef struct	s_fork
// {
// }				t_fork;

// typedef struct	s_philos
// {
// 	pthread_t	philo_id;
// 	t_fork		*left_fork;
// 	t_fork		*right_fork;
// }				t_philos;

int	ft_atoi(const char *nptr);
int	check_input(t_philo *philo, int ac, char **av);

#endif
