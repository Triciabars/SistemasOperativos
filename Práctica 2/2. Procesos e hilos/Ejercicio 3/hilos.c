#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#define N 5
typedef struct {
	int id_usuario;
	int prioridad; //char
} usuario;

void *thread_usuario(void *arg) 
{
	
	usuario usuario_local = *((usuario *) arg);
	free(arg);
	printf (" Thread %d, %d,%d \n",pthread_self(), usuario_local.id_usuario, usuario_local.prioridad);
	
}

int main(int argc, char* argv[])
{
	//Inicializar y crear memoria dinámica, no estoy segura si aquí o en la función
	pthread_t usuarios[N];

	//Creamos el hilo
	for (int i = 1; i <= N; i++){
	usuario *arg = (usuario *) malloc(sizeof(usuario));
	arg->id_usuario = i;
	arg->prioridad = i%2;
	pthread_create (&usuarios[i-1], NULL,thread_usuario, arg);
	}
	for (int i = 1; i <= N; i++){
		pthread_join(&usuarios[i-1], NULL);
	}

	return 0;
}
