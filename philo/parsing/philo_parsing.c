#include "../header/philo.h"

int	input_parser(int ac, char **av, t_global *global)
{
	if (!check_input(av, ac))
		fill_stack(av, ac, global);
	else
		return (1);
	return (0);
}
//
// int	main(int ac, char **av)
// {
// 	t_global	global;
//
// 	if (ac == 5 || ac == 6)
// 	{
// 		if (!input_parser(ac, av, &global))
// 		{
// 			printf("%d\n", global.input.number_of_philo);
// 			printf("%d\n", global.input.time_to_die);
// 			printf("%d\n", global.input.time_to_eat);
// 			printf("%d\n", global.input.time_to_sleep);
// 			printf("%d\n", global.input.number_of_meals);
// 		}
// 		else
// 			printf("error\n");
// 	}
// 	else
// 		return (0);
// 	return (0);
// }
