#include <bits/types/struct_timeval.h>
#include <pthread.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct	s_philo
{
	int				id;
	pthread_t		thr;
	long			last_meal;
	struct s_global	*global;
}				t_philo;

typedef struct	s_input
{
	long	number_of_philos;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	number_of_meals;
}				t_input;

typedef struct	s_global
{
	pthread_mutex_t	*fork;
	struct timeval	start_time;
	t_philo			*philo;
	t_input			input;
	int				is_he_dead;
}				t_global;

long	timestamp(t_global *global)
{
	struct timeval	current;
	struct timeval	start;
	long			ret;

	start = global->start_time;
	gettimeofday(&current, NULL);
	ret = (current.tv_sec - start.tv_sec) * 1000 + (current.tv_usec - start.tv_usec) / 1000;
	return (ret);
}

void	philo_sleep(t_global *global, long sleeping_time)
{
	long	start;

	start = timestamp(global);
	while (!global->is_he_dead && timestamp(global) - start < sleeping_time)
		usleep(100);
}

void	*philo_routine(void *input)
{
	t_philo	*philo;
	long		id;
	int			left;
	int			right;

	philo = (t_philo *)input;
	id = philo->id;
	left = (id + 1) % philo->global->input.number_of_philos;
	right = id;
	if (philo->id % 2 != 0)
		philo_sleep(philo->global, philo->global->input.time_to_eat);
	while (!philo->global->is_he_dead)
	{
		printf("[%lu] - philo[%lu] is thinking\n", timestamp(philo->global), id);
		pthread_mutex_lock(&philo->global->fork[right]);
		pthread_mutex_lock(&philo->global->fork[left]);
		printf("[%lu] - philo[%lu] is eating\n", timestamp(philo->global), id);
		philo_sleep(philo->global, philo->global->input.time_to_eat);
		pthread_mutex_unlock(&philo->global->fork[left]);
		pthread_mutex_unlock(&philo->global->fork[right]);
		philo->last_meal = timestamp(philo->global);
		printf("[%lu] - philo[%lu] is sleeping\n", timestamp(philo->global), id);
		philo_sleep(philo->global, philo->global->input.time_to_sleep);
	}
	return (NULL);
}

void	init_var(t_global *global)
{
	global->input.number_of_philos = 3;
	global->input.time_to_sleep = 60;
	global->input.time_to_eat = 60;
	global->input.time_to_die = 190;
	global->input.number_of_meals = 0;
}

void	*philo_death(void *input)
{
	t_global	*global;
	int			i;
	long		no_meal_time;

	global = (t_global *)input;
	while (!global->is_he_dead)
	{
		i = 0;
		while (i < global->input.number_of_philos)
		{
			no_meal_time = timestamp(global) - global->philo[i].last_meal;
			if (no_meal_time > global->input.time_to_die)
			{
				printf("[%lu] - philo[%d] is dead 💀\n", timestamp(global), global->philo[i].id);
				global->is_he_dead = 1;
				return (NULL);
			}
			i++;
		}
		// usleep(1000);
	}
	return (NULL);
}

int	main()
{
	int				i;
	t_global		global;
	pthread_t		supervisor;

	gettimeofday(&global.start_time, NULL);
	i = 0;
	global.is_he_dead = 0;
	init_var(&global);
	global.fork = malloc(sizeof(pthread_mutex_t) * global.input.number_of_philos);
	global.philo = malloc(sizeof(t_philo) * global.input.number_of_philos);
	while (i < global.input.number_of_philos)
	{
		pthread_mutex_init(&global.fork[i], NULL);
		i++;
	}
	i = 0;
	while (i < global.input.number_of_philos)
	{
		global.philo[i].id = i;
		global.philo[i].last_meal = timestamp(&global);
		global.philo[i].global = &global;
		pthread_create(&global.philo[i].thr, NULL, philo_routine, &global.philo[i]);
		i++;
	}
	i = 0;
	pthread_create(&supervisor, NULL, philo_death, &global);
	pthread_join(supervisor, NULL);
	while (i < global.input.number_of_philos)
	{
		pthread_join(global.philo[i].thr, NULL);
		i++;
	}
	i = 0;
	while (i < global.input.number_of_philos)
	{
		pthread_mutex_destroy(&global.fork[i]);
		i++;
	}
	free(global.fork);
	free(global.philo);
}
