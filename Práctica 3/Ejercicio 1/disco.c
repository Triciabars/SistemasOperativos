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

void Cliente(int id_usuario, int is_vip)
{
	printf("Cliente con id [%d] es vip o no [%d] (0 no es vip 1 es vip).\n", id_usuario, is_vip);
	if (is_vip == 1)	enter_vip_client(id_usuario);
	else enter_normal_client(id_usuario);
	dance(id_usuario, is_vip);
	disco_exit(id_usuario, is_vip);
}

void *client(void *arg)
{
	while (1)
	{
		int id_cliente = (int)arg; // obtener el id del usario
		int is_vip = (int)arg;
		Cliente(id_cliente, is_vip);
	}
}

int main(int argc, char *argv[])
{

	int i;
	int fd;
	pthread_t *clientes;
	fd = fopen(argv[1], O_CREAT | O_RDWR | O_TRUNC, 0666);
	fscanf(fd, "%d", &num_clientes);
	if (num_clientes > CAPACITY)
	{
		fprintf(stderr, "%s", "No me pongas mas clientes que el máximo de aforo (5) por favor\n");
		exit(EXIT_FAILURE);
	}
	clientes = malloc(num_clientes * sizeof(int));
	pthread_mutex_init(&mutex, NULL);		//Mutex
	pthread_cond_init(&hayespacio, NULL);
	pthread_cond_init(&nohayvips, NULL);
	for (i = 0; i < num_clientes; i++) {
		int* datoscliente;
		int isvip;
		datoscliente[0] = i;
		datoscliente[1] = fscanf(fd, "%d", &isvip);
		if (datoscliente[1] == 1) n_clientesvip++;
		pthread_create(&clientes[i], NULL, client, datoscliente);
	}

	for (i = 0; i < num_clientes; i++)
	{
		pthread_join(clientes[i], NULL);
	}
	fclose(fd);
	return 0;

}
