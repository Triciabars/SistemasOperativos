#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define CAPACITY 5
#define VIPSTR(vip) ((vip) ? "  vip  " : "not vip")

int num_clientes, n_clientesvip;
pthread_mutex_t mutex;
pthread_cond_t nohayvips, hayespacio;

typedef struct{
	int id;
	int isvip;
}client_datos;

void enter_normal_client(int id)
{
	pthread_mutex_lock(&mutex);
	while (n_clientesvip != 0)
		pthread_cond_wait(&nohayvips, &mutex);
	while (num_clientes == CAPACITY)
		pthread_cond_wait(&hayespacio, &mutex);
	num_clientes++;
	pthread_mutex_unlock(&mutex);
}

void enter_vip_client(int id)
{
	pthread_mutex_lock(&mutex);
	while (num_clientes == CAPACITY)
		pthread_cond_wait(&hayespacio, &mutex);
	num_clientes++;
	if (n_clientesvip == 0)
		pthread_cond_signal(&nohayvips);
	//Se desbloquea mutex
	pthread_mutex_unlock(&mutex);
}
void dance(int id, int isvip)
{
	printf("Client %2d (%s) dancing in disco\n", id, VIPSTR(isvip));
	sleep((rand() % 3) + 1);
}
void disco_exit(int id, int isvip)
{
	pthread_mutex_lock(&mutex);
	num_clientes--;
	pthread_cond_signal(&hayespacio);
	pthread_mutex_unlock(&mutex);
}


void *client(void *arg){ //el argumento que le pasamos es la estructura

	client_datos *datoscliente2 = (client_datos *) arg;
	
	//printf("Cliente con id [%d] es vip o no [%d] (0 no es vip 1 es vip).\n", datoscliente2->id, datoscliente2->is_vip);
	if (datoscliente2->is_vip == 1)	enter_vip_client(datoscliente2->id);
	else enter_normal_client(datoscliente2->id);
	dance(datoscliente2->id, datoscliente2->is_vip);
	disco_exit(datoscliente2->id, datoscliente2->is_vip);
	
}
int main(int argc, char *argv[]){
	
	//Initialize values
	int i, isvip;
	FILE *fs;
	client_datos *datoscliente;
	pthread_t *clientes;	

	//Open file and read number of clients
	fs = fopen(argv[1], "r");
	fscanf(fs, "%d", &num_clientes);

	//Check capacity
	if (num_clientes > CAPACITY){
		fprintf(stderr, "%s", "No me pongas mas clientes que el máximo de aforo (5) por favor\n");
		exit(EXIT_FAILURE);
	}

	clientes = malloc(num_clientes * sizeof(pthread_t));
	pthread_mutex_init(&mutex, NULL);		//Mutex
	pthread_cond_init(&hayespacio, NULL);
	pthread_cond_init(&nohayvips, NULL);

	for (i = 0; i < num_clientes; i++) {
		datoscliente = malloc(sizeof(client_datos));
		fscanf(fs, "%d\n", &isvip); //\n es para ver que se lea el siguiente
		
		datoscliente->id = i;
		datoscliente->isvip = isvip;
		
		pthread_create(&clientes[i], NULL, client, datoscliente);
	}

	for (i = 0; i < num_clientes; i++){
		pthread_join(clientes[i], NULL);
	}

	fclose(fs);
	return 0;

}

