/*En este ejercicio vamos a crear un programa mostrar.c similar al comando cat, que reciba como parámetro el nombre de un fichero y lo muestre por la salida estándar. 
En este caso asumiremos que es un fichero estándar. Además, nuestro programa recibirá dos argumentos que parsearemos con getopt (consultar su página de manual):

-n N: indica que queremos saltarnos N bytes desde el comienzo del fichero o mostrar únicamente los N últimos bytes del fichero. Que se haga una cosa o la otra depende de la presencia o no de un segundo flag -e. Si el flag -n no aparece N tomará el valor 0.
-e: si aparece, se leerán los últimos N bytes del fichero. Si no aparece, se saltarán los primeros N bytes del fichero.
El programa debe abrir el fichero indicado en la línea de comandos (consultar optind en la página de manual de getopt) y después situar el marcador de posición en la posición correcta antes de leer. Para ello haremos uso de la llamada al sistema lseek (consultar la página de manual). 
Si el usuario ha usado el flag -e debemos situar el marcador N bytes antes del final del fichero. Si el usuario ha usado el flag -e debemos avanzar el marcador N bytes desde el comienzo del fichero.

Una vez situado el marcador de posición, debemos leer leer byte a byte hasta el final de fichero, escribiendo cada byte leído por la salida estándar (descriptor 1).*/




#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <err.h>


int main(int argc, char *argv[])
{
    int opt, fd;
	int buffer[100];
	char* token;
	FILE* file=NULL;
	int c,ret;
	int n = 0;
	
	
	if (argc!=3) { //si han pasado menos de tres argumentos por parametro
		fprintf(stderr,"Usage: %s <file_name> <tam>\n",argv[0]); //error chicoooo
		exit(1);
	}

	 /* Open file */
    file = open(argv[1], O_RDONLY); //con el open se hace con int
	 if(file == -1){
        err(2,"The input file %s could not be opened",argv[1]);
	}

    //Off_t lseek(int fd (file descripter), off_t offset, int whence (posicion pointer))
	while((opt = getopt(argc, argv, "n:e")) != -1) {   //parseamos con getopt los argumentos que se reciban
		//el : implica que vas a tener un valor adicional aderido a la opcion anterior (en este caso n)
		switch(opt) {
		case 'n': //queremos saltarnos N bytes desde el comienzo del fichero
			//fd=open(file, O_RDWR); //se abre el archivo para  leer solo
			n=atoi(optarg); //usar conversor atoi porque optarg es siempre string
			lseek(file, n, SEEK_SET); //el puntero se coloca a offset bytes
			break;
		case 'e': //se leen los ultimos N bytes del fichero
			//https://www.youtube.com/watch?v=a37WtG6KdYM
			//fd=open(file, O_RDWR); //se abre el archivo para leer solo
			n=atoi(optarg); //usar conversor atoi porque optarg es siempre string      atoi(argv[2]);
			lseek(file, -n, SEEK_END); //El número de bytes indicado en N se suma a la dirección actual y el puntero se coloca en la dirección resultante.
			break;
		default: /* si n no aparece , N tomara el valor 0 */
			
			//leer byte a byte hasta el final del fichero
	


    /* Read file byte by byte */
    while ((c = fread(buffer, size, 1, file)) == 1) {
        /* Print byte to stdout */
        ret=fwrite(buffer, size, 1, stdout);

        if (ret==EOF){
            fclose(file);
            err(3,"putc() failed!!");
        }
    }

	fclose(file);
	return 0;
		}
	}
}