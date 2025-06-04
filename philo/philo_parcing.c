# include "philo.h"

int	check_len(char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	if (len > 10)
		return (1);
	return (0);
}

static int	num_check(char *s)
{
	int	i;

	i = 0;
	
	if (check_len(s)) // TODO
		return (1);
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static void	fill_struct(t_input *input, int value, int order)
{
	if (order == 0)
		input->num_of_philo = value;
	else if (order == 1)
		input->time_to_die = value;
	else if (order == 2)
		input->time_to_eat = value;
	else if (order == 3)
		input->time_to_sleep = value;
	else if (order == 4)
		input->num_of_eats = value;
}

int	check_input(t_input *input, int ac, char **av)
{
	int			i;
	int			num;
	long int	buff;

	i = 1;
	num = 0;
	buff = 0;
	while (i < ac)
	{
		if (num_check(av[i]))
		{
			buff = ft_atoi(av[i]);
			if (buff <= 0 || buff > INT_MAX)
				return (0);
			fill_struct(input, buff, num);
			num++;
		}
		else
			return (0);
		i++;
	}
	return (1);
}
