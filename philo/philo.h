#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct	s_philo
{
	int	num_of_philo;
	int	time_to_eat;
	int	time_to_sleep;
	int	time_to_die;
	int	num_of_eats;
}				t_philo;

int	ft_atoi(const char *nptr);
int	check_input(t_philo *philo, int ac, char **av);

#endif
