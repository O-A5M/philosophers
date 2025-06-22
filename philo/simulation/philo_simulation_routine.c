#include "../include/philo.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

static int	read_death(t_death death)
{
	int	ret;

	pthread_mutex_lock(&death.death_protect);
	ret = death.death_flag;
	pthread_mutex_unlock(&death.death_protect);
	return (ret);
}

long	timestamps(t_global *global)
{
	struct timeval	current;
	struct timeval	start;
	long			ret;

	start = global->start_time;
	gettimeofday(&current, NULL);
	ret = (current.tv_sec - start.tv_sec) * 1000 + (current.tv_usec - start.tv_usec) / 1000;
	return (ret);
}

long	last_meal(t_global *global, int id, int flag)
{
	long	ret;

	ret = 0;
	if (flag == 0)
	{
		pthread_mutex_lock(&global->philo[id].last_meal.meal_protect);
		ret = global->philo[id].last_meal.last_meal;
		pthread_mutex_unlock(&global->philo[id].last_meal.meal_protect);
	}
	else
	{
		pthread_mutex_lock(&global->philo[id].last_meal.meal_protect);
		global->philo[id].last_meal.last_meal = timestamps(global);
		pthread_mutex_unlock(&global->philo[id].last_meal.meal_protect);
	}
	return (ret);
}

void	smart_sleep(t_global *global, long sleeping_time)
{	
	long	start;

	start = timestamps(global);
	while (!read_death(global->death) && timestamps(global) - start < sleeping_time)
		usleep(100);
}

void	*philo_routine(void *input)
{
	t_philo	*philo;
	int		left;
	int		right;

	philo = (t_philo *)input;
	left = philo->id;
	right = (left + 1) % philo->global->input.number_of_philo;
	if (philo->id % 2 != 0)
		smart_sleep(philo->global, philo->global->input.time_to_eat);
	while (!read_death(philo->global->death))
	{
		printf("%ld %d is thinking\n", timestamps(philo->global), left);
		pthread_mutex_lock(&philo->global->forks[left]);
		printf("%ld %d has taken a fork!\n", timestamps(philo->global), left);
		pthread_mutex_lock(&philo->global->forks[right]);
		printf("%ld %d has taken a fork!\n", timestamps(philo->global), left);
		printf("%ld %d is eating\n", timestamps(philo->global), left);
		smart_sleep(philo->global, philo->global->input.time_to_eat);
		last_meal(philo->global, left, 1);
		pthread_mutex_unlock(&philo->global->forks[left]);
		pthread_mutex_unlock(&philo->global->forks[right]);
		printf("%ld %d is sleeping\n", timestamps(philo->global), left);
		smart_sleep(philo->global, philo->global->input.time_to_sleep);
	}
	return (NULL);
}

void	*death_tracker(void *input)
{
	t_global	*global;
	int			i;
	long		no_meal_time;

	global = (t_global *)input;
	while (!read_death(global->death))
	{
		i = 0;
		while (i < global->input.number_of_philo)
		{
			no_meal_time = timestamps(global) - last_meal(global, i, 0);
			if (no_meal_time > global->input.time_to_die)
			{
				pthread_mutex_lock(&global->death.death_protect);
				global->death.death_flag = 1;
				pthread_mutex_unlock(&global->death.death_protect);
				printf("%ld %d is dead\n", timestamps(global), i);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
