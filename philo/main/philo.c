#include "../include/philo.h"

int	main(int ac, char **av)
{
	t_input	input;

	memset(&input, 0, sizeof(input));
	if (!parsing_input(ac, av, &input))
		start_simulation(input);
	else
	 printf("Error\n");
}
