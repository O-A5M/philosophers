#include "philo.h"

int	main(int ac, char **av)
{
	t_philo	philo;

	if (ac == 5 || ac == 6)
	{
		if (check_input(&philo, ac, av))
		{
			printf("%d\n", philo.num_of_philo);
			printf("%d\n", philo.time_to_die);
			printf("%d\n", philo.time_to_eat);
			printf("%d\n", philo.time_to_sleep);
			if (ac == 6)
				printf("%d\n", philo.num_of_eats);
		}
	}
	else
		return (1);
}
