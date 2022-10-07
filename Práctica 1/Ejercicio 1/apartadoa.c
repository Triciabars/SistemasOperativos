/*
   ¿Qué comando se debe emplear para generar el ejecutable del programa (show_file) invocando directamente al compilador gcc (sin usar make)?
      $ gcc -Wall -c "nombredelfichero"
 
 
 Indique dos comandos para llevar a cabo respectivamente la compilación del programa (generación de fichero objeto) y el enlazado del mismo de forma independiente.
      $ gcc -c -o prueba.o prueba.c
 

*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) { 
    FILE* file=NULL;
    int c,ret;
    int buffer[10];//el buffer

    if (argc!=2) {
        fprintf(stderr,"Usage: %s <file_name>\n",argv[0]);
        exit(1);
    }

    /* Open file */
    if ((file = fopen(argv[1], "r")) == NULL)
        err(2,"The input file %s could not be opened",argv[1]);

      /* Read file byte by byte */
    while ((c = fread(buffer, 1, 1, file)) == 1) { //el ==1 porque significa que ha leido 1 byte, si deja de leer seria 0 y acabaria el while
        /* Print byte to stdout */
        ret=fwrite(buffer, 1, 1, stdout); //stdout para que se escriba por pantalla, sino lee y vuelve a escribir lo mismo

        if (ret==0){ //cuando se hayan escrito 0 bloques, porque significa que es el final del archivo
            fclose(file);
            err(3,"fwrite() failed!!");
        }
    }

    fclose(file);
    return 0;
}
