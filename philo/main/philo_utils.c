#include "../header/philo.h"

void	error_message(void)
{
	printf("Wrong input!!\n");
	printf("Please consider the following rules:\n");
	printf("	The input must be in the following order\n");
	printf("		->Number of philosophers\n");
	printf("		->Time to die\n");
	printf("		->Time to eat\n");
	printf("		->Time to sleep\n");
	printf("		->Number of meals to end simulation(optional)\n");
	printf("	*Enter only positive numbers\n");
	printf("	*The number must be positive\n");
	printf("	*The number must be equal or smaller than INT_MAX\n");
	printf("	*It has to be different from zero\n");
}
