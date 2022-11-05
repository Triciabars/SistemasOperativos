#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h>
#define _POSIX_SOURCE



int main(int argc, char **argv){
	pid_t pid;
	int status_code;
	char **args;
	int resultado;

	args=&argv[1];
	pid=fork();//Creamos el hijo
	execvp(argv[0], *args);//excvp
	alarm(5);
	resultado= kill(pid, SIGKILL);
	printf ("Enviado SIGKILL al hijo con resultado %d\n", resultado);
	 resultado = wait(&status_code);
	 printf("Abortado %d con senial %d\n",
	 resultado,status_code);

	
		

	return 0;
}

