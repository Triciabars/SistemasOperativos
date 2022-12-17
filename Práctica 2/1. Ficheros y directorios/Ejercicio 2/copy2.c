#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h> //para readlink

void copy(int fdo, int fdd)
{
	int n;
	do {
		n = read(fdo, buffer, 512);
		if (n < 512) {
			write(fdd, buffer, n);
		}
		else write(fdd, buffer, 512);
	} while (n > 0);
		close(fdo);
		close(fdd);
		if (n < 0) {
			perror(" Error en la copia ");
		}
}

void copy_regular(char *orig, char *dest)
{

}

void copy_link(char *orig, char *dest){
	//int* mem;
	size_t bufsize; 
	ssize_t buffersize, result;
	char* buffer;

	buffersize = p_statbuf.st_size + 1;
	buffer = malloc(buffersize); //localizacion inicial del buffer
	if (buffer == NULL) {    
        fprintf(stderr, "La aplicacion no pudo reservar memoria y se va a cerrar!\n");
        exit(EXIT_FAILURE);
		//añadir el null 
    }
	
	//ssize_t readlink(const char *restrict pathname, char *restrict buf, size_t bufsiz);
	if((result = readlink(argv[1], buffer, buffersize))!=-1){//copiar en el buffer la ruta del fichero apuntado 
		if(result==-1){
			perror("readlink");
			exit(EXIT_FAILURE);

		}
	}

	if(symlink(orig, dest)!=0){ //creando el enlace de dest que apunte tambien a origen
		perror("error en symlink()");
		unlink(orig);
	}
	else{
		unlink(orig);
		unlink(dest);
	}
	free(buffer); //liberar la memoria reservada
}

int main(int argc, char *argv[]){
	
	int fdo, fdd, type, size;
	int buffer[512];
	//ver si es un enlace simbolico con lstat
	struct stat p_statbuf;

	if (argc != 3) {
		perror("Introduzca el número de parametros correcto (2). <nombre fichero origen> <nombre fichero destino>");
	}
	if ((fdo = open(argv[1], O_RDONLY)) == -1) {
		perror(" Error al abrir src ");
	}
	if ((fdd = open(argv[2], O_RDWR | O_CREAT), 7777) == -1) {
		perror(" Error al abrir dst ");
		close(fdo);
	}

	//comprobar tipo de enlace del fichero origen --> int lstat(const char *path, struct stat *buf)
    if (lstat(argv[1], &p_statbuf) < 0) {  /* if error occured */
        perror("No se pudo llamar a lstat");
        exit(1);  /* end progam here */
    }

    if (S_ISLNK(p_statbuf.st_mode) == 1) { //es un enlace simbolico
       copy_link(argv[1], argv[2]);
    } 
	else if (S_ISREG(p_statbuf.st_mode) == 1) { //es un enlace regular, se copia normal
        copy(fdo, fdd);
	}
	else { 
        perror("ERROR. No es un enlace simbolico ni regular, no nos vale para copiar");
        exit(1);  /* end progam here */
    }

	return 0;
}
