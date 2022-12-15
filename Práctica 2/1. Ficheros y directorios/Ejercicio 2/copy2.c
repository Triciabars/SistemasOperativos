#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

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
	int* mem;
	size_t bufsize = 300; 
	ssize_t result;
	char path[250]; //array donde se guarda

	char* buf = malloc(p_statbuf.st_size + 1); //localizacion inicial del buffer
	if((result = readlink(path, buffer,(p_statbuf.st_size + 1))))!=-1){//copiar en el buffer la ruta del fichero apuntado 
		buf[result] = '\0';
	}

	if(symlink(orig, dest)!=0){ //creando el enlace de dest que apunte tambien a origen
		perror("error en symlink()");
		unlink(orig);
	}
	else{
		unlink(orig);
		unlink(dest);
	}
	//free(mem); //liberar la memoria reservada
}

int main(int argc, char *argv[])
{
	int fdo, fdd, type, size;
	int buffer[512];

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

	//ver si es un enlace simbolico con lstat
	struct stat p_statbuf;

    if (lstat(argv[1], &p_statbuf) < 0) {  /* if error occured */
        perror("No se pudo llamar a lstat");
        exit(1);  /* end progam here */
    }

    if (S_ISLNK(p_statbuf.st_mode) == 1) { //es un enlace simbolico
       copy_link(argv[1], argv[2]);
    } 
	if (S_ISREG(p_statbuf.st_mode) == 1) { //es un enlace regular, se copia normal
        copy(fdo, fdd);
	}
	else { 
        perror("ERROR. No es un enlace simbolico ni regular, no nos vale para copiar");
        exit(1);  /* end progam here */
    }



	
	return 0;
}
