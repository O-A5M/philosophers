#include "philo.h"
#include <bits/types/struct_timeval.h>
#include <sys/time.h>

void	philo_sleep(int sleep_duration)
{
	struct timeval	start_time;

	gettimeofday(&start_time, NULL);
	usleep (sleep_duration);
	printf("%d\n", start_time.tv_usec/1000);
}

void	philo_eat(int eat_time)
{
	struct timeval	start_time;

	gettimeofday(start_time, NULL);
	usleep(eat_time);
	printf("%d/n", start_time.tv_usec/1000);
}
