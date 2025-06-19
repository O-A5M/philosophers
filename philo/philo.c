#include "philo.h"

int	main(int ac, char **av)
{
	t_global	global;

	if (ac == 5 || ac == 6)
	{
		if (!input_parser(ac , av , &global))
		{
			start_simulation(&global);
		}
		else
		{
			error_message();
			return (1);
		}
	}
	else
	{
		error_message();
		return (1);
	}
	return (0);
}
