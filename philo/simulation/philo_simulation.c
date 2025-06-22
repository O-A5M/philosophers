#include "../include/philo.h"

static void	init_data(t_global *global, t_philo *philo, t_input input)
{
	int	i;

	i = 0;
	global->philo = philo;
	gettimeofday(&global->start_time, NULL);
	pthread_mutex_init(&global->death.death_protect, NULL);
	pthread_mutex_lock(&global->death.death_protect);
	global->death.death_flag = 0;
	pthread_mutex_unlock(&global->death.death_protect);
	global->input = input;
	global->forks = malloc(sizeof(pthread_mutex_t) * global->input.number_of_philo);
	while (i < input.number_of_philo)
		pthread_mutex_init(&global->forks[i++], NULL);
	pthread_create(&global->death_monitor, NULL, death_tracker, global);
	philo->global = global;
}

static void	init_data_philo(t_global *global)
{
	int i;

	i = 0;
	while (i < global->input.number_of_philo)
		pthread_mutex_init(&global->philo[i++].last_meal.meal_protect, NULL);
	i = 0;
	while (i < global->input.number_of_philo)
		global->philo[i++].last_meal.last_meal = timestamps(global);
}

static void	create_philo(t_global *global)
{
	int i;

	i = 0;
	init_data_philo(global);
	while (i < global->input.number_of_philo)
	{
		global->philo[i].id = i;
		global->philo[i].global = global;
		global->philo[i].meal_counter = 0;
		pthread_create(&global->philo[i].thread, NULL, philo_routine, &global->philo[i]);
		i++;
	}
}

void	start_simulation(t_input input)
{
	t_philo		philo[input.number_of_philo];
	t_global	global;
	int			index;

	index = 0;
	init_data(&global, philo, input);
	create_philo(&global);
	while (index < global.input.number_of_philo)
		pthread_join(global.philo[index++].thread, NULL);
	pthread_join(global.death_monitor, NULL);
	index = 0;
	while (index < input.number_of_philo)
		pthread_mutex_destroy(&philo[index++].last_meal.meal_protect);
	pthread_mutex_destroy(&global.death.death_protect);
	free (global.forks);
}
