#include "../header/philo.h"

int	input_parser(int ac, char **av, t_global *global)
{
	if (!check_input(av, ac))
		fill_stack(av, ac, global);
	else
		return (1);
	return (0);
}
