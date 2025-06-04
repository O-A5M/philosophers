#include "philo.h"

int	main(int ac, char **av)
{
	t_input		input;
	pthread_t	*philo_thread;

	if (ac == 5 || ac == 6)
	{
		//check for errors
		//and store the input
		check_input(&input, ac, av);
		//creating threads and mutexes
		//and allocating memory for them 
		philos_init(); // TODO
		//Start of the simulation
		start_sim(); // TODO
		//Cleaning in case of:
		//errors.
		//end simulation.
		//philo dies.
		clean(); // TODO
	}
	else
	{
		error_message(); // TODO
	}
}
