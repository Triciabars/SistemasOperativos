#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define NUMITER 3
int *caldero;
sem_t *m, *empty, *full;

int getServingsFromPot(void)
{
	unsigned long id = (unsigned long) getpid();
	sem_wait(&m);
	if (caldero == 0) {
		printf("Salvaje %d: caldero vacío\n", id);
		sem_post(&empty);
		sem_wait(&full);
	}
	printf("Salvaje %d sirviendo ración del caldero %d\n",
			id, caldero);
	caldero--;
	sem_post(&m);
}

void eat(void)
{
	unsigned long id = (unsigned long) getpid();
	printf("Savage %lu eating\n", id);
	sleep(rand() % 5);
}

void savages(void)
{
	while(1) {
		getServingsFromPot();
		eat();
	}
}

int main(int argc, char *argv[])
{
	int i;
	pthread_t *tid;

	tid = malloc(NUMITER * sizeof(pthread_t));
	if (tid == NULL){
		perror("malloc tid");
		exit(EXIT_FAILURE);
	}

	sem_init(&m, 0, 1);
	sem_init(&empty, 0, 0);
	sem_init(&full, 0, 0);

	for (i = 0; i < NUMITER; i++)
		pthread_create(&tid[i], NULL, savages, (void*) i);

	for (i = 0; i < n; i++)
		pthread_join(tid[i], NULL);

	
	sem_destroy(&m);
	sem_destroy(&empty);
	sem_destroy(&full);
	return 0;
}
