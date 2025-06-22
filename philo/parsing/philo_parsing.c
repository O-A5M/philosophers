#include "../include/philo.h"

static int	is_it_number(char *s)
{
	int	index;

	index = 0;
	if (s[index] == '-' || s[index] == '+')
		index++;
	while (s[index])
	{
		if (s[index] > '9' || s[index] < '0')
			return (1);
		index++;
	}
	return (0);
}

static long	ft_atoi(const char *nptr)
{
	int			i;
	int			sign;
	long		ret;

	i = 0;
	sign = 1;
	ret = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -sign;
		i++;
	}
	while (nptr[i] <= '9' && nptr[i] >= '0')
		ret = (ret * 10) + (nptr[i++] - '0');
	return (ret * sign);
}

static int	check_input(char **s, int ac)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (is_it_number(s[i]))
			return (1);
		else if (ft_atoi(s[i]) > INT_MAX || ft_atoi(s[i]) <= 0)
			return (1);
		i++;
	}
	return (0);
}

static void	fill_stack(t_input *input, int ac, char **av)
{
	input->number_of_philo = ft_atoi(av[1]);
	input->time_to_die = ft_atoi(av[2]);
	input->time_to_eat = ft_atoi(av[3]);
	input->time_to_sleep = ft_atoi(av[4]);
	input->number_of_meals = 0;
	if (ac == 6)
		input->number_of_meals = ft_atoi(av[5]);
}

int	parsing_input(int ac, char **av, t_input *input)
{
	if (ac == 5 || ac == 6)
	{
		if (check_input(av, ac))
			return (1);
		else
			fill_stack(input, ac, av);
	}
	else
		return (1);
	return (0);
}
