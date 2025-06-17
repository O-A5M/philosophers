#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdbool.h>

#define NUM_PHILOS 3

typedef struct	s_philo
{
    int			id;
    pthread_t	thread;
    long		last_meal;
}				t_philo;

pthread_mutex_t forks[NUM_PHILOS];
pthread_mutex_t print_mutex = PTHREAD_MUTEX_INITIALIZER;
struct timeval start_time;

int time_to_eat = 30;
int time_to_sleep = 30;
int time_to_die = 60;

bool simulation_running = true;
t_philo philosophers[NUM_PHILOS];

long timestamp_ms()
{
    struct timeval now;
    gettimeofday(&now, NULL);

    long sec = now.tv_sec - start_time.tv_sec;
    long usec = now.tv_usec - start_time.tv_usec;
    return sec * 1000 + usec / 1000;
}

void print_status(int id, const char *msg)
{
    pthread_mutex_lock(&print_mutex);
    if (simulation_running)
        printf("[%ld ms] Philosopher %d %s\n", timestamp_ms(), id, msg);
    pthread_mutex_unlock(&print_mutex);
}

void smart_sleep(int ms)
{
    long start = timestamp_ms();
    while (simulation_running && (timestamp_ms() - start) < ms)
        usleep(100);
}

void	*philosopher_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    int left = philo->id;
    int right = (philo->id + 1) % NUM_PHILOS;

    while (simulation_running)
	{
        print_status(philo->id, "is thinking");
        if (philo->id % 2 == 0)
		{
            pthread_mutex_lock(&forks[left]);
            pthread_mutex_lock(&forks[right]);
        }
		else
		{
            pthread_mutex_lock(&forks[right]);
            pthread_mutex_lock(&forks[left]);
        }
        print_status(philo->id, "is eating");
        philo->last_meal = timestamp_ms();
        smart_sleep(time_to_eat);
        pthread_mutex_unlock(&forks[left]);
        pthread_mutex_unlock(&forks[right]);
        print_status(philo->id, "is sleeping");
        smart_sleep(time_to_sleep);
    }
    return NULL;
}

void *monitor_routine(void *arg)
{
    (void)arg;
    while (simulation_running) {
        for (int i = 0; i < NUM_PHILOS; i++)
		{
            long time_since_meal = timestamp_ms() - philosophers[i].last_meal;
            if (time_since_meal > time_to_die)
			{
                pthread_mutex_lock(&print_mutex);
                printf("[%ld ms] Philosopher %d died 💀\n", timestamp_ms(), philosophers[i].id);
                simulation_running = false;
                pthread_mutex_unlock(&print_mutex);
                return NULL;
            }
        }
        usleep(100);
    }
    return NULL;
}

int main()
{
    gettimeofday(&start_time, NULL);

    // Init mutexes
    for (int i = 0; i < NUM_PHILOS; i++)
        pthread_mutex_init(&forks[i], NULL);

    // Init philosophers
    for (int i = 0; i < NUM_PHILOS; i++) {
        philosophers[i].id = i;
        philosophers[i].last_meal = timestamp_ms();
        pthread_create(&philosophers[i].thread, NULL, philosopher_routine, &philosophers[i]);
    }

    // Launch monitor
    pthread_t monitor;
    pthread_create(&monitor, NULL, monitor_routine, NULL);

    // Wait for monitor to end simulation
    pthread_join(monitor, NULL);

    // Clean up
    for (int i = 0; i < NUM_PHILOS; i++)
        pthread_join(philosophers[i].thread, NULL);

    for (int i = 0; i < NUM_PHILOS; i++)
        pthread_mutex_destroy(&forks[i]);

    pthread_mutex_destroy(&print_mutex);
    return 0;
}

