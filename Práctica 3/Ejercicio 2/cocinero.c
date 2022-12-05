#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <signal.h>

#include <pthread.h>
#include <err.h>
#include <sys/stat.h>

#define M 10
int *caldero;
sem_t *m, *empty, *full;
int finish = 0;

void putServingsInPot(int servings)
{
	sem_wait(empty);
	*caldero += servings;
	printf("Llenando caldero %d\n", *caldero);
	sem_post(full);
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
	// Initialize
	int i, shd;
	struct sigaction sa;
	sigset_t set;
	
	// Handler
	sigfillset(&set);
	sa.sa_mask = set;
	sa.sa_flags = 0;
	sa.sa_handler = handler;
	sigaction(SIGTERM, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);
	
	// Create semmaphores
	m = sem_open("/MUTEX", O_CREAT, 0700,1);
	empty = sem_open("/EMPTY", O_CREAT, 0700, 1);
	full = sem_open("/FULL", O_CREAT, 0700,0);
	
	// Create mmap
	shd = shm_open("/CALDERO", O_CREAT|O_EXCL|O_RDWR, S_IRUSR | S_IWUSR); //CON OPEN() TAMBIEN DIAPO 63
	ftruncate(shd, sizeof(int));
	// Apply mmap
	caldero = (int*) mmap(NULL, sizeof(int), PROT_WRITE|PROT_READ, MAP_SHARED, shd, 0);
	*caldero = 0;
	
	// Run main cook program
	cook();
	
	// Empty everything
	munmap(caldero, sizeof(int));
	shm_unlink("/CALDERO");
	close(shd);
	sem_close(m);
	sem_close(empty);
	sem_close(full);
	sem_unlink("/MUTEX");
	sem_unlink("/EMPTY");
	sem_unlink("/FULL");
	
	return 0;
}
