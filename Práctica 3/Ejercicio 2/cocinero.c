#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define M 10
int *caldero;
sem_t m, empty, full;
int finish = 0;

void putServingsInPot(int servings)
{
	sem_wait(&empty);
	*caldero += servings;
	printf("Llenando caldero %d\n", *caldero);
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
	int i, shd;
	m = sem_open("/MUTEX", O_CREAT|O_RDWR, 0700,1);
	empty = sem_open("/EMPTY", O_CREAT|O_RDWR, 0700, 1);
	full = sem_open("/FULL", O_CREAT|O_RDWR, 0700,0);
	shd = shm_open("/CALDERO", O_CREAT|O_EXCL|O_RDWR, S_ISUSR | S_IWUSR); //CON OPEN() TAMBIEN DIAPO 63
	ftruncate(shd, sizeof(int));
	caldero = (int*) mmap(NULL, M * sizeof(int), PROT_WRITE|PROT_READ, MAP_SHARED, shd, 0);
	*caldero = 0;

	cook();
	
	munmap(caldero, MAX_BUFFER * sizeof(int));
	close(shd);
	sem_close(&m);
	sem_close(&empty);
	sem_close(&full);
	sem_unlink("/MUTEX");
	sem_unlink("/EMPTY");
	sem_unlink("/FULL");
	shm_unlink("/CALDERO");

	return 0;
}
