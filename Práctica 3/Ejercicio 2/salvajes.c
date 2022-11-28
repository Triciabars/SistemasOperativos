#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <signal.h>

#define NUMITER 10
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
	*caldero--;
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
	while(1) {
		getServingsFromPot();
		eat();
	}
}

int main(int argc, char *argv[])
{
	int i, shd;

	m = sem_open("/MUTEX", O_CREAT|O_RDWR, 0700,1);
	empty = sem_open("/EMPTY", O_CREAT|O_RDWR, 0700, 1);
	full = sem_open("/FULL", O_CREAT|O_RDWR, 0700,0);
	shd = shm_open("/CALDERO", O_CREAT|O_EXCL|O_RDWR, S_IRUSR | S_IWUSR); //CON OPEN() TAMBIEN DIAPO 63
	ftruncate(shd, sizeof(int));
	caldero = (int*) mmap(NULL, NUMITER * sizeof(int), PROT_WRITE|PROT_READ, MAP_SHARED, shd, 0);
	
	savages();
	close(shd);
	munmap(caldero, NUMITER * sizeof(int));
	
	sem_close(m);
	sem_close(empty);
	sem_close(full);
	sem_unlink("/MUTEX");
	sem_unlink("/EMPTY");
	sem_unlink("/FULL");
	shm_unlink("/CALDERO");
	return 0;
}
