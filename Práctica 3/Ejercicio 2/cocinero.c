#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define M 10
int *caldero;
sem_t *m, *empty, *full;
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
	m = sem_open("/MUTEX", O_CREAT|O_RDWR, 0700,1);
	empty = sem_open("/EMPTY", O_CREAT|O_RDWR, 0700,0);
	full = sem_open("/FULL", O_CREAT|O_RDWR, 0700,0);
	caldero = (int*) mmap(NULL, M * sizeof(int), PROT_WRITE, MAP_SHARED);
	pthread_create(&tid_cook, NULL, cocinero, NULL);
	
	pthread_join(tid_cook, NULL);
	munmap(caldero, MAX_BUFFER * sizeof(int));
	sem_close(&m);
	sem_close(&empty);
	sem_close(&full);
	sem_unlink("/MUTEX");
	sem_unlink("/EMPTY");
	sem_unlink("/FULL");

	return 0;
}
