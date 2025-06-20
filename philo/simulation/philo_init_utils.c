#include "../header/philo.h"

long	timestamp(t_global *global)
{
	struct timeval	start_time;
	long			ret;

	gettimeofday(&start_time, NULL);
	ret = (global->start_sim.tv_sec - start_time.tv_sec) * 1000
			+ (global->start_sim.tv_usec - start_time.tv_usec) / 1000;
	return (ret);
}

void	ft_sleep(long time, t_global *global)
{
	long	start;

	start = timestamp(global);
	while (!global->is_dead.is_dead && timestamp(global) - start < time)
		usleep(100);
}
