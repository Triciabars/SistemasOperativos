#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <signal.h>

#define NUMITER 15
int *caldero;
sem_t *m, *empty, *full;

int getServingsFromPot(void)
{
	unsigned long id = (unsigned long) getpid();
	sem_wait(m);
	if (*caldero == 0) {
		printf("Salvaje %lu: caldero vacío\n", id);
		sem_post(empty);
		sem_wait(full);
	}
	printf("Salvaje %lu sirviendo ración del caldero %d\n",
			id, *caldero);
	(*caldero)--;
	sem_post(m);
}

void eat(void)
{
	unsigned long id = (unsigned long) getpid();
	printf("Savage %lu eating\n", id);
	sleep(rand() % 5);
}

void savages(void)
{
	for(int i=0; i<NUMITER; i++) {
		getServingsFromPot();
		eat();
	}
}

int main(int argc, char *argv[])
{
	int i, shd;

	// Load already created semaphores
	m = sem_open("/MUTEX", 0);
	empty = sem_open("/EMPTY", 0);
	full = sem_open("/FULL", 0);
	
	// Load mmap 
	shd = shm_open("/CALDERO", O_RDWR, 0); 
	caldero = (int*) mmap(NULL, sizeof(int), PROT_WRITE|PROT_READ, MAP_SHARED, shd, 0);
	
	// Run main program
	savages();
	
	// Close everything
	close(shd);
	sem_close(m);
	sem_close(empty);
	sem_close(full);
	return 0;
}
