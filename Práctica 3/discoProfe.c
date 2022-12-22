#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <err.h>

#define CAPACITY 5
#define VIPSTR(vip) ((vip) ? "  vip  " : "not vip")

//tickets, el usuario puede tener el id (nombre) y el ticket (numero que chequea si tiene que entrar o no tiene que entrar)
int num_clients = 0;
int nturn = 0; //va del 1 al n
int nticket = 0; //el ticket puede ser un numero random
int vturn = 0;
int vticket = 0;

int num_clients_inside = 0;
int vip_esperando = 0;

pthread_mutex_t m;
pthread_cond_t empty;

typedef struct{
	int id;
	int isvip;
}client_datos;

void enter_normal_client(int id){
	
    int myticket; //definimos el ticket del cliente en ese momento

    pthread_mutex_lock(&m);
    myticket = nticket++;

    //el ticket es diferente al turno (me toca entrar?) o si hay vip esperando o si hay o no sitio para mi 
    while(myticket!=turn || vip_esperando || num_clients_inside >= CAPACITY){
        printf("Client %2d (not vip) waiting on the queue\n", id);
        pthread_cond_wait(&empty, &m); //esperamos
    }
    num_clients_inside++; //aumentamos el numero de cleitnes dentro
    nturn++; //aumentamos turno
    pthread_cond_broadcast(&empty); //llamamos a todos los demas
    printf("Client %2d (not vip) entering the disco\n", id);
    pthread_mutex_unlock(&m);
}

void enter_vip_client(int id)
{
	 int myticket;

    pthread_mutex_lock(&m);
    myticket = vticket++;

    //si es el turno del vip o hay capacidad
    while(myticket!=vturn || num_clients_inside >= CAPACITY){
        vip_esperando++;
        printf("Client %2d (vip) waiting on the queue\n", id);
        pthread_cond_wait(&empty, &m); //se pone esperando hasta que salte la condicion
        vip_esperando--; //el vip deja de esperar
    }
    num_clients_inside++;
    vturn++;
    pthread_cond_broadcast(&empty); //volver a llamar a todos
    printf("Client %2d (vip) entering the disco\n", id);
    pthread_mutex_unlock(&m);

}
void dance(int id, int isvip)
{
	printf("Client %2d (%s) dancing in disco\n", id, VIPSTR(isvip));
	sleep((rand() % 3) + 1);
}
void disco_exit(int id, int isvip)
{
	int myticket;

    pthread_mutex_lock(&m);
	num_clients_inside--;
    pthread_cond_broadcast(&empty);
	printf("Client %2d (%s) exits the disco\n", id, VIPSTR(isvip));
	pthread_mutex_unlock(&m);
}


void *client(void *arg){ //el argumento que le pasamos es la estructura

	client_datos *pca = (client_datos *)arg;

    printf("Starting client %2d\n"; pca->id, VIPSTR(pca->isvip)):

    //checkeamos si es vip o no vip
    if(pca->isvip)  
        enter_vip_client(pca->id);
    else 
        enter_normal_client(pca->id);
    
    dance(pca->id, pca->isvip);
    disco_exit(pca->id, pca->isvip);
   
    free(pca);

    return NULL;
	
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

