#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <signal.h>

#define NUMITER 3
int *caldero;
sem_t *m, *empty, *full;

int getServingsFromPot(void)
{
	sem_wait(m);
	if (*caldero == 0) {
		printf("Salvaje: caldero vacío\n");
		sem_post(empty);
		sem_wait(full);
	}
	printf("Salvaje sirviendo ración del caldero %d\n", *caldero);
	*caldero--;
	sem_post(m);
}

void eat(void)
{
	printf("Savage eating\n");
	sleep(rand() % 5);
}

void savages(void)
{
	for(int i=0; i<NUMITER; i++) {
		getServingsFromPot();
	}
	eat();
}

int main(int argc, char *argv[])
{
	int i, shd;

	m = sem_open("/MUTEX", 0);
	empty = sem_open("/EMPTY", 0);
	full = sem_open("/FULL", 0);
	shd = shm_open("/CALDERO", O_CREAT|O_EXCL|O_RDWR, S_IRUSR | S_IWUSR); //CON OPEN() TAMBIEN DIAPO 63
	ftruncate(shd, sizeof(int));
	caldero = (int*) mmap(NULL, 10 * sizeof(int), PROT_WRITE|PROT_READ, MAP_SHARED, shd, 0);
	
	savages();
	
	munmap(caldero, 10 * sizeof(int));
	close(shd);
	sem_close(m);
	sem_close(empty);
	sem_close(full);
	return 0;
}
