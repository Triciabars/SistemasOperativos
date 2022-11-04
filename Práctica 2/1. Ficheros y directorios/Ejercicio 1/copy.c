#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void copy(int fdo, int fdd)
{
	int n;
	int buffer[512];
	do {
		n = read (fdo, buffer, 512) ;
		if (n < 512) {
			write (fdd, buffer, n);
		}
		else write (fdd, buffer, 512) ;
	} while ( n > 0) ;
		close ( fdo );
		close ( fdd );
		if (n < 0) {
		perror ( " Error en la copia " );
	}
}

int main(int argc, char *argv[]) //recibe 2 parámetros (nom fichero origen y nom fichero destino)
{
	int fdo , fdd;
	if(argc != 3){
		perror ( "Introduzca el número de parametros correcto (2). <nombre fichero origen> <nombre fichero destino>");
	}
	if (( fdo = open ( argv[1] , O_RDONLY )) == -1) {
		perror ( " Error al abrir src ");
	}
	if (( fdd = open ( argv[2] , O_RDONLY | O_WRONLY | O_CREAT ) , 7777) == -1) {
		perror ( " Error al abrir dst ");
		close ( fdo );
	}
	copy(fdo, fdd);	
	return 0;
}
/*
El programa debe realizar la copia en bloques de 512B. Para ello se reservará
un buffer de 512 bytes como almacenamiento intermedio. El programa debe ir leyendo bloques de 512 bytes del fichero
origen y escribiendo los bytes leídos en el fichero destino. Debéis tener en cuenta que si el tamaño del fichero no es
múltiplo de 512 bytes la última vez no se leerán 512 bytes, sino lo que quede hasta el final del fichero (es decir, read
devolverá menos de 512). Por ello siempre se debe escribir en el fichero destino tantos bytes como se hayan leído del
fichero origen (read devolverá el número de bytes leídos).
El alumno debe consultar las páginas de manual de las siguientes llamadas al sistema: open, read, write y close. En la
página de manual de open prestad especial atención a los flags de apertura, teniendo que usar en este caso O_RDONLY,
O_WRONLY, O_CREAT, O_TRUNC.
Para comprobar el efecto de O_TRUNC, se sugiere al alumno que antes de ejecutar su programa de copia, cree un
fichero con cualquier contenido que se llame como el fichero destino. Después puede copiar otro fichero usando el
nombre elegido para el fichero destino y comprobar que el contenido anterior desaparece al usarse el flag O_TRUNC.
Para comprobar el funcionamiento correcto de nuestro programa podemos usar los comandos de shell diff y hexdump
(este último para ficheros binarios).
*/