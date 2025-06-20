#include "../header/philo.h"
#include <alloca.h>
#include <pthread.h>

int	create_philos(t_global *global)
{
	int	index;

	index = 0;
	global->philo = malloc(sizeof(t_philo) * global->input.number_of_philo);
	if (!global->philo)
		return (1);
	global->fork = malloc(sizeof(pthread_mutex_t) * global->input.number_of_philo);
	if (!global->fork)
	{
		free(global->philo);
		return (1);
	}
	while (index < global->input.number_of_philo)
	{
		global->philo[index].id = index;
		global->philo[index].global = global;
		pthread_create(&global->philo[index].thread, NULL, philo_routine, &global->philo[index]);
		index++;
	}
	pthread_create(&global->supervisor, NULL, death_checker, &global);
	pthread_mutex_init(&global->is_dead.end_of_simulation, NULL);
	index = 0;
	while (index < global->input.number_of_philo)
		pthread_mutex_init(&global->fork[index++], NULL);
	return (0);
}

void	start_simulation(t_global *global)
{
	int	index;

	index = 0;
	create_philos(global);
	while (index < global->input.number_of_philo)
	{
		pthread_join(global->philo[index].thread, NULL);
		pthread_mutex_destroy(&global->fork[index]);
		index++;
	}
	index = 0;
	pthread_join(global->supervisor, NULL);
	pthread_mutex_destroy(&global->is_dead.end_of_simulation);
}
