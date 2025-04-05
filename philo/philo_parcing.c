# include "philo.h"

int	num_check(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	fill_struct(t_philo *philo, int value, int order)
{
	if (order == 0)
		philo->num_of_philo = value;
	else if (order == 1)
		philo->time_to_die = value;
	else if (order == 2)
		philo->time_to_eat = value;
	else if (order == 3)
		philo->time_to_sleep = value;
	else if (order == 4)
		philo->num_of_eats = value;
}

int	check_input(t_philo *philo, int ac, char **av)
{
	int	i;
	int	num;

	i = 1;
	num = 0;
	while (i < ac)
	{
		if (num_check(av[i]))
		{
			fill_struct(philo, ft_atoi(av[i]), num);
		}
	}
}
