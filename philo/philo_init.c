#include "philo.h"

void	*philos_work(void *philo)
{
	while (1)
	{
	}
}

int	create_philos(t_philo *philo, pthread_t philo_thread)
{
	int	i;
	pthread_t	thread[philo->num_of_philo];

	i = 0;
	while (i < philo->num_of_philo)
	{
		if((pthread_create(&thread[i], NULL, philos_work, philo) != 0)
				exit(1);
		i++;
	}
}
