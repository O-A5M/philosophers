#include "philo.h"

int	main(int ac, char **av)
{
	t_philo		philo;
	pthread_t	*philo_thread;

	if (ac == 5 || ac == 6)
	{
		if (!check_input(&philo, ac, av))
			return (1);
		else
		{
			create_philos();
		}
	}
	else
		return (1);
}
