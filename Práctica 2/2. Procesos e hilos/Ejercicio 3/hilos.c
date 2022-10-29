#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void *thread_usuario(void *arg) //puntero con estructura de dos campos (entero y caracter)
{
	//usando memoria dinamica crear variable
	//Duda si mostrarlo aquí, pero no lo paso?
	printf (" Thread % ld \n " ,( long unsigned int) pthread_self ());
	printf(arg[0],arg[1]);//error?
	pthread_exit (0) ;
}

int main(int argc, char* argv[])
{
	//Inicializar y crear memoria dinámica, no estoy segura si aquí o en la función
	pthread_t *pthr_arr_usuarios;
	int* num_user=(int*)malloc(sizeof(int));
	char* priority= (char*)malloc(sizeof(char));
	pthr_arr_usuarios = (pthread_t *)malloc(sizeof(pthread_t));

	num_user=argv[0];
	priority=argv[1];//lo de impares y pares no sé cómo funcionaría aquí
	//Creamos el hilo
	for (int i = 0; i < (argc/2); i++)
	pthread_create (&pthr_arr_usuarios[i], NULL,thread_usuario,NULL);//duda no paso argumentos?
	return 0;
}
//crea un hilo por cada usuario