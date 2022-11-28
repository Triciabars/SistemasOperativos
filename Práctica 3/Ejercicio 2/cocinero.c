#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define M 10
int caldero = 0;
sem_t m, empty, full;
int finish = 0;

void putServingsInPot(int servings)
{
	sem_wait(&empty);
	caldero += raciones;
	printf("Llenando caldero %d\n", caldero);
	sem_post(&full);
}

void cook(void)
{
	while(!finish) {
		putServingsInPot(M);
	}
}

void handler(int signo)
{
	finish = 1;
}

int main(int argc, char *argv[])
{
	int i;
	pthread_t tid_cook;

	sem_init(&m, 0, 1);
	sem_init(&empty, 0, 0);
	sem_init(&full, 0, 0);
	
	pthread_create(&tid_cook, NULL, cocinero, NULL);
	
	pthread_join(tid_cook, NULL);
	
	sem_destroy(&m);
	sem_destroy(&empty);
	sem_destroy(&full);

	return 0;
}
