/*En este ejercicio vamos a usar la biblioteca de pthreads, por lo que será necesario compilar y enlazar con la opción
-pthread.
-Escribir un programa hilos.c que cree un hilo para cada usuario, pasándole a cada uno como argumento el puntero a una
estructura que contenga dos campos: un entero, que será el número de usuario, y un caracter, que indicará si el usuario
es prioritario (P) o no (N).
-El programa deberá crear una variable para el argumento de cada hilo usando memoria dinámica, inicializar dicha
variable con el número de usuario y su prioridad (los pares serán prioritarios y los impares no lo serán), crear los hilos y
esperar a que finalicen.
Cada hilo copiará sus argumentos en variables locales, liberará la memoria dinámica reservada para los mismos,
averiguará cuál es su identificador e imprimirá un mensaje con su identificador, el número de usuario y su prioridad.
El alumno debe consultar las páginas de manual de: pthread_create, pthread_join, pthread_self.
Probar a crear solamente una variable para el argumento de todos los hilos, dándole el valor correspondiente a cada hilo
antes de la llamada a pthread_create. Explicar qué sucede y cuál es la razón.*/

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#define N 5
typedef struct {
	int id_usuario; //numero de usuario
	int prioridad; //char que indica si es prioridad(P) o no(N)
} usuario;  //struct usuario

void *thread_usuario(void *arg) 
{
	
	usuario usuario_local = *((usuario *) arg);
	free(arg); 
	printf (" Thread %ld, %d,%d \n",pthread_self(), usuario_local.id_usuario, usuario_local.prioridad);
	
}

int main(int argc, char* argv[])
{
	//Inicializar y crear memoria dinámica, no estoy segura si aquí o en la función
	pthread_t usuarios[N]; //hilos con todos los usuarios

	//Creamos el hilo
	for (int i = 1; i <= N; i++){
		usuario *arg = (usuario *) malloc(sizeof(usuario)); //memoria dinamica 
		arg->id_usuario = i; //dar valores
		arg->prioridad = i%2; 
		pthread_create (&usuarios[i-1], NULL,thread_usuario, arg); //crear hilo
	}
	for (int i = 1; i <= N; i++){
		pthread_join(usuarios[i-1], NULL);
	}

	return 0;
}
