#include "../header/philo.h"
#include <pthread.h>

int	read_death(t_global *global)
{
	int	death;

	pthread_mutex_lock(&global->is_dead.end_of_simulation);
	death = global->is_dead.is_dead;
	pthread_mutex_unlock(&global->is_dead.end_of_simulation);
	return (death);
}

long	last_meal(t_global *global, int i, int flag)
{
	long	ret;

	ret = 0;
	if (flag == 0)
	{
		pthread_mutex_lock(&global->philo[i].last_meal.meal_mutex);
		global->philo[i].last_meal.last_meal = timestamp(global);
		pthread_mutex_unlock(&global->philo[i].last_meal.meal_mutex);
	}
	else
	{
		pthread_mutex_lock(&global->philo[i].last_meal.meal_mutex);
		ret = global->philo[i].last_meal.last_meal;
		pthread_mutex_unlock(&global->philo[i].last_meal.meal_mutex);
	}
	
	return (ret);
}

void	*death_checker(void *input)
{
	t_global	*global;
	int			index;

	global = (t_global *)input;
	while (!read_death(global))
	{
		index = 0;
		while (index < global->input.number_of_philo)
		{
			if ((timestamp(global) - last_meal(global, index, 1)) > global->input.time_to_die)
			{
				pthread_mutex_lock(&global->is_dead.end_of_simulation);
				global->is_dead.is_dead = 1;
				pthread_mutex_unlock(&global->is_dead.end_of_simulation);
				printf("is dead\n");
				return (NULL);
			}
			index++;
		}
		usleep(100);
	}
	return (NULL);
}

void	*philo_routine(void *input)
{
	t_philo	*philo;
	int		left;
	int		right;

	philo = (t_philo *)input;
	left = philo->id;
	right = (left + 1) % philo->global->input.number_of_philo;
	if (left % 2 != 0)
		ft_sleep(philo->global->input.time_to_eat, philo->global);
	while (!read_death(philo->global))
	{
		printf("[%ld] - philo[%d] is thinking\n", timestamp(philo->global), left);
		if (left < right)
		{
			pthread_mutex_lock(&philo->global->fork[left]);
			pthread_mutex_lock(&philo->global->fork[right]);
		}
		else
		{
			pthread_mutex_lock(&philo->global->fork[right]);
			pthread_mutex_lock(&philo->global->fork[left]);
		}
		printf("[%ld] - philo[%d] is eating\n", timestamp(philo->global), left);
		last_meal(philo->global, left, 0);
		ft_sleep(philo->global->input.time_to_eat, philo->global);	
		pthread_mutex_unlock(&philo->global->fork[right]);
		pthread_mutex_unlock(&philo->global->fork[left]);
		printf("[%ld] - philo[%d] is sleeping\n", timestamp(philo->global), left);
		ft_sleep(philo->global->input.time_to_sleep, philo->global);
	}
	return (NULL);
}
