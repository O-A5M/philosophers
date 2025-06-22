#include "../header/philo.h"

long	timestamp(t_global *global)
{
	struct timeval	start_time;
	long			ret;

	gettimeofday(&start_time, NULL);
	ret = (start_time.tv_sec - global->start_sim.tv_sec) * 1000
			+ (start_time.tv_usec - global->start_sim.tv_usec) / 1000;
	return (ret);
}

void	ft_sleep(long time, t_global *global)
{
	long	start;

	start = timestamp(global);
	while (!read_death(global) && timestamp(global) - start < time)
		usleep(100);
}
