#include "../header/philo.h"

static void	init_meal(t_global *global)
{
	int	index;

	index = 0;
	global->is_dead.is_dead = 0;
	while (index < global->input.number_of_philo)
	{
		global->philo[index].last_meal = 0;
		index++;
	}
}

int	create_philos(t_global *global)
{
	int	index;

	index = 0;
	global->philo = malloc(sizeof(t_philo) * global->input.number_of_philo);
	if (!global->philo)
		return (1);
	init_meal(global);
	global->fork = malloc(sizeof(pthread_mutex_t) * global->input.number_of_philo);
	if (!global->fork)
	{
		free(global->philo);
		return (1);
	}
	while (index < global->input.number_of_philo)
		pthread_mutex_init(&global->fork[index++], NULL);
	pthread_mutex_init(&global->is_dead.end_of_simulation, NULL);
	index = 0;
	while (index < global->input.number_of_philo)
	{
		global->philo[index].id = index;
		global->philo[index].global = global;
		pthread_create(&global->philo[index].thread, NULL, philo_routine, &global->philo[index]);
		index++;
	}
	pthread_create(&global->supervisor, NULL, death_checker, &global);
	return (0);
}

void	start_simulation(t_global *global)
{
	int	index;

	index = 0;
	create_philos(global);
	pthread_join(global->supervisor, NULL);
	while (index < global->input.number_of_philo)
	{
		pthread_join(global->philo[index].thread, NULL);
		index++;
	}
	index = 0;
	while (index < global->input.number_of_philo)
	{
		pthread_mutex_destroy(&global->fork[index]);
		index++;
	}
	pthread_mutex_destroy(&global->is_dead.end_of_simulation);
}
