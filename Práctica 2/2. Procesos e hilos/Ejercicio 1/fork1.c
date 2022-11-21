#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/*programa que crea dos hijos: uno no cambia de ejecutable y otro si */


int main(int argc, char **argv){
	pid_t pid, pid_h;
	int status_code;
	char **args;
	
	//get argumentos
	args=&argv[1]; //coger todos los parámetros a partir de la llamada

	pid = fork(); //se crea el hijo

	if(pid==0){ //proceso hijo
		printf("Soy el proceso hijo con PID %d. Mi padre es %d Global\n", getpid(), getppid());
	}	
	else{ //proceso padre
		printf("Soy el proceso padre con PID %d. Mi padre es %d Global\n", getpid(), getppid());
		wait(NULL); //el proceso padre espera a que termine el hijo
	}

	pid_h=fork(); //se hace la segunda llamada al fork y se vuelve a crear un hijo
		
		if(pid_h==0){ //si es el hijo del prcoeso hijo
			printf("Soy el proceso hijo con PID %d. Mi padre es %d Global\n", getpid(), getppid());
			status_code = execvp(argv[0], *args);
			if (status_code == -1) {
				printf("Process did not terminate correctly\n");
				exit(1);
			}
		}
		else{ //padre del proceso hijo
			wait(NULL);
			printf("Soy el proceso padre con PID %d. Mi padre es %d Global\n", getpid(), getppid());
			//pid_t waitpid(pid_t pid, int *status, int options);
			status_code = execvp(argv[0], *args);
			if (status_code == -1) {
				printf("Process did not terminate correctly\n");
				exit(1);
			}
		}
		//int execvp(const char* command, char* argv[]);
		

	return 0;
}
