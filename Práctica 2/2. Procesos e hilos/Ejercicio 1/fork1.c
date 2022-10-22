#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/*programa que crea dos hijos: uno no cambia de ejecutable y otro si */


int main(int argc, char **argv){
	pid_t pid, pid_h;
	int status_code;

	pid = fork(); //se crea el hijo

	if(pid==0){ //proceso hijo
		printf("Soy el proceso hijo con PID %d. Mi padre es %d Global\n", getpid(), getppid());
		pid_h=fork(); //se hace la segunda llamada al fork y se vuelve a crear un hijo
		
		if(pid_h==0){ //si es el hijo del prcoeso hijo
			printf("Soy el proceso hijo con PID %d. Mi padre es %d Global\n", getpid(), getppid());
		
		else{ //padre del proceso hijo
			printf("Soy el proceso padre con PID %d. Mi padre es %d Global\n", getpid(), getppid());
			//pid_t waitpid(pid_t pid, int *status, int options);
			if(waitpid(getpid, &status_code, WNOHANG) == -1){ //esperar al pid concreto
					perror("waitpid");
					exit(EXIT_FAILURE);
				}
			}
		}	//int execvp(const char* command, char* argv[]);
		status_code = execvp(argv, argv);
		if (status_code == -1) {
			printf("Process did not terminate correctly\n");
			exit(1);
		}
	}
	
	else{ //proceso padre
	printf("Soy el proceso padre con PID %d. Mi padre es %d Global\n", getpid(), getppid());
	wait(NULL); //el proceso padre espera a que termine el hijo
	}

	return 0;
}
