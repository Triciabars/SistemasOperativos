#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h>
#define _POSIX_SOURCE


int funcion(pid_t pid){
	return kill(pid, SIGKILL);

}

int main(int argc, char **argv){
	pid_t pid;
	int status_code;
	char **args;
	int resultado;
	int funcion(pid_t); 

	struct sigaction act;

	// Recpogemos input como array
	args=&argv[1];
	pid=fork();//Creamos el hijo
	if(pid=0){
		execvp(args[0], args);//excvp
	}
	else{
		// Generar handler
		act.sa_handler = (int)(*funcion)(pid);// llama a una funcion que mata al hijo
		act.sa_flags=0;// flag inicial

		// Sigaction -> asignar handler a una señal
		sigaction(SIGALRM, &act, NULL);

		// Lanzar alarma
		alarm(5);

		// wait para que lance hijo
		waitpid(pid, NULL, 0);
	}

		

	return 0;
}
