#include "../include/philo.h"

int	read_death(t_death death)
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

void	ft_print(t_philo *philo, char *message)
{
	if (!read_death(philo->global->death))
	{
		pthread_mutex_lock(&philo->global->ft_print);
		printf("%ld %d %s\n", timestamps(philo->global), philo->id, message);
		pthread_mutex_unlock(&philo->global->ft_print);
	}
}
