//Bibliotecas
//Habituales
#include <stdio.h> //Input y output functions
#include <unistd.h>//Acceso a POSIX

//Enteros y strings
#include <string.h>//Strings
#include <stdlib.h> //Para convertir enteros en carácteres

//Ficheros
#include <fcntl.h> //Se utiliza para manipular el descriptor del fichero
#include <sys/types.h>//Para obtener información sobre ficheros
#include <sys/wait.h>//Esta biblioteca va siempre con la anterior

/*Parámetros: 
    -->fdo: fichero origen
    -->fdd: fichero destino*/
void copy(int fdo, int fdd)
{
	int size; //Número de bytes que voy a leer
    	int buffer[512];//Para realizar la copia en bloques de 512 bytes creo un buffer intermedio
	do{
        //ssize_t read(int fd_que_estamos_leyendo, void *buffer, size_t count);
        size=read(fdo, buffer, 512); //Devuelve los bytes leidos hasta el último número indicado 
        write(fdd, buffer, size); //Escribe hasta count bytes, ssize_t write(int fd, const void *buf, size_t count);
   	 }while(size>0);
		close(fdd);
        	close(fdo);
        	if(size<0){
            		perror("Error en copia");
       		 }
}

int main(int argc, char *argv[])
{
	int fdo, fdd;
  	if(argc != 3){
	perror ( "Introduzca el número de parametros correcto (2). <nombre fichero origen> <nombre fichero destino>");
	}
	if (( fdo = open ( argv[1] , O_RDONLY )) == -1) {  //En caso de error de lectura y lo estamos abriendo en modo abrir solo "O_RDONLY"
		perror ( " Error al abrir src ");
	}
	if (( fdd = open ( argv[2] ,  O_CREAT| O_RDWR ) , 7777  ) == -1) {  //Damos todos los permisos a todos y en este caso estamos abrirendo para leer o escribir si existe o creaamos sino el fichero.
		close ( fdo );
        	perror ( " Error al abrir dst ");
	}
	copy(fdo, fdd);

	return 0;
}
	
