#include "philo.h"

int	main(int ac, char **av)
{
	t_philo	philo;

	if (ac == 5 || ac == 6)
	{
		if (check_input(&philo, ac, av))
		{

		}
	}
	else
		return (1);
}
