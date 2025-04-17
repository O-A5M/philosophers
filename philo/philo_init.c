#include "philo.h"

void	philos_work(void *voi);

int	create_philos(t_philo *philo, pthread_t philo_thread)
{
	int	i;

	i = 0;
	while (i < philo->num_of_philo)
	{
		pthread_create(philo_thread, NULL, &philos_work, NULL);
	}
}
