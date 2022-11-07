#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* programa que crea N hijos siguiendo un grado de dependencias. Usa las
 * versiones de execl y execlp */

int main()
{
	pid_t pid_1, pid_2, pid_3, pid_4, pid_5, pid_6, pid_7, pid_8;
	
	// Hijo 1
	pid_1=fork();
	if (pid_1==0){
		execlp("echo", "echo", "soy P1\n", NULL);
		exit(-1);
	}
	waitpid(pid_1, NULL, 0);
	
	// Hijo 2
	pid_2=fork();
	if (pid_2==0){
		execl("/bin/echo", "echo", "soy P2\n", NULL);
		exit(-1);
	}
	waitpid(pid_2, NULL, 0);
	
	//Hijo 5
	pid_5=fork();
	if (pid_5==0){
		execlp("echo", "echo", "soy P5\n", NULL);
		exit(-1);
	}
	waitpid(pid_5, NULL, 0);

	//Hijo 7
	pid_7=fork();
	if (pid_7==0){
		execlp("echo", "echo", "soy P7\n", NULL);
		exit(-1);
	}
	waitpid(pid_7, NULL, 0);
	
	//Hijo 3
	pid_3=fork();
	if (pid_3==0){
		execlp("echo", "echo", "soy P3\n", NULL);
		exit(-1);
	}
	waitpid(pid_3, NULL, 0);
	
	//Hijo 4
	pid_4=fork();
	if (pid_4==0){
		execl("/bin/echo", "echo", "soy P4\n", NULL);
		exit(-1);
	}
	waitpid(pid_4, NULL, 0);

	//Hijo 6
	pid_6=fork();
	if (pid_6==0){
		execl("/bin/echo", "echo", "soy P6\n", NULL);
		exit(-1);
	}
	waitpid(pid_6, NULL, 0);

	//Hijo 8
	pid_8=fork();
	if (pid_8==0){
		execl("/bin/echo", "echo", "soy P8\n", NULL);
		exit(-1);
	}
	waitpid(pid_8, NULL, 0);


	return 0;
}
