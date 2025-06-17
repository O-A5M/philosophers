#include <bits/types/struct_timeval.h>
#include <pthread.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct	s_philo
{
	int	id;
	pthread_t	thr;
	long		last_meal;
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
	t_global	*global;
	long		id;

	global = (t_global *)input;
	id = global->philo->id;
	while (!global->is_he_dead)
	{
		printf("[%lu] - philo[%lu] is thinking\n", timestamp(global), id);
		pthread_mutex_lock(&global->fork[id]);
		pthread_mutex_lock(&global->fork[(id + 1) % global->input.number_of_philos]);
		philo_sleep(global, global->input.time_to_eat);
		printf("[%lu] - philo[%lu] is eating\n", timestamp(global), id);
		pthread_mutex_unlock(&global->fork[id]);
		pthread_mutex_unlock(&global->fork[(id + 1) % global->input.number_of_philos]);
		philo_sleep(global, global->input.time_to_sleep);
		printf("[%lu] - philo[%lu] is sleeping\n", timestamp(global), id);
	}
	return (NULL);
}

void	init_var(t_global *global)
{
	global->input.number_of_philos = 3;
	global->input.time_to_sleep = 30;
	global->input.time_to_eat = 30;
	global->input.time_to_die = 60;
	global->input.number_of_meals = 0;
}

void	*philo_death(void *input)
{
	t_global	*global;
	int			i;
	long		no_meal_time;

	global = (t_global *)input;
	i = 0;
	while (!global->is_he_dead)
	{
		while (i < global->input.number_of_philos)
		{
			no_meal_time = timestamp(global) - global->philo[i].last_meal;
			if (no_meal_time > global->input.time_to_die)
			{
				printf("philo[%d] is dead 💀\n", global->philo[i].id);
				global->is_he_dead = 1;
				return (NULL);
			}
			i++;
		}
		usleep(100);
	}
	return (NULL);
}

int	main()
{
	int				i;
	static struct timeval	start_time;
	t_global		global;
	pthread_t		supervisor;

	gettimeofday(&start_time, NULL);
	i = 0;
	global.is_he_dead = 0;
	init_var(&global);
//	parcing_input(&global.input); //TODO
	// mutex initialisation
	global.fork = malloc(sizeof(pthread_mutex_t) * global.input.number_of_philos);
	global.philo = malloc(sizeof(t_philo) * global.input.number_of_philos);
	while (i < global.input.number_of_philos)
	{
		pthread_mutex_init(&global.fork[i], NULL);
		i++;
	}
	i = 0;
	// philos initialisation
	while (i < global.input.number_of_philos)
	{
		global.philo[i].id = i;
		global.philo[i].last_meal = timestamp(&global);
		pthread_create(&global.philo[i].thr, NULL, philo_routine, &global);
		i++;
	}
	i = 0;
	pthread_create(&supervisor, NULL, philo_death, &global);
	while (i < global.input.number_of_philos)
	{
		pthread_mutex_destroy(&global.fork[i]);
		i++;
	}
	i = 0;
	pthread_join(supervisor, NULL);
	while (i < global.input.number_of_philos)
	{
		pthread_join(global.philo[i].thr, NULL);
		i++;
	}
}
