#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    FILE* file=NULL;
    int c,ret;
    //int cont = 0;
    int buffer[100];//el buffer
    int parametroUsuario;

    if (argc!=2) {
        fprintf(stderr,"Usage: %s <file_name>\n",argv[0]);
        exit(1);
    }

    //leer parametro por usuario
    printf("Dime el numero de bytes:\n");
    scanf("%d", &parametroUsuario); //parametro leido 
    printf("El numero que pusiste fue: %d", parametroUsuario);

    /* Open file */
    if ((file = fopen(argv[1], "r")) == NULL)
        err(2,"The input file %s could not be opened",argv[1]);

      /* Read file byte by byte */
    while ((c = fread(buffer, parametroUsuario, 1, file)) != EOF) {
        /* Print byte to stdout */
        ret=fwrite(buffer, parametroUsuario, 1, file);

        if (ret==EOF){
            fclose(file);
            err(3,"putc() failed!!");
        }
    }

    fclose(file);
    return 0;
}  


/*
VARIACION 


*/