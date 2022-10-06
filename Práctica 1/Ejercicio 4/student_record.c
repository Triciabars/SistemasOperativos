#include <stdio.h>
#include <student_record.h>


int main(){
    FILE *f1; //puntero de tipo file

        //crear fichero
        f1 = fopen("database.dat", "wb"); //con wb hacemos que fopen cree el archivo binario
        if (f1==NULL){
            exit(1);
        }

            //funcion que acepta como parametro el listado de regsitros en formato ASCII
        //asi como el numero de registros y devuelve la representacion binaria de los mismos hecho con malloc()
        student_t* parse_records(char* records[], int nr_records){

        }

        //vuelca al fichero binario abierto los registros de estudiastes apsados como parametro
        int dump_entries(student_t* entries, int nr_entries, FILE* students){
            int stEscritos;
            students = fopen("fichero.dat", "wb"); //para escribir en binario
            //fwrite (direcc_dato, tamaño_dato, numero_datos, punt_fichero)
            stEscritos = fwrite(&entries.student_id, sizeof(int),1, students);

        }

        //lee informacion de un fichero binario de registor de estudiantes y devuelve la informacion de la cabecera
        //la memoria que se retorna debe reservarse con malloc() dentro de la propia funcion
        student_t* read_student_file(FILE* students, int* nr_entries){
            students = fopen("fichero.dat", "rb"); //apertura del fichero para lectura en binario
        }

        //lee una cadena de carácteres terminada en ´\0´ del fichero que se pasa por paramrtro, 
        // reservando la cantidad de memoria adecuada
        char* loadstr(FILE* students){
            students = fopen("fichero.dat", "rb"); //apertura del fichero para lectura en binario
            //fread (direcc_dato, tamaño_dato, numero_datos,punt_fichero);
            

        }

    }

    /*
        //leer fichero
        void addStudent(student_t student){
            //añadir estudiante en el fichero
            //comprobar que el estudiante no existe
            if(){ //si no existe el estudiante
            student_t nuevo;
                //scanf("%i", &nuevo.student_id)
            printf("Se añadio un estudiante nuevo");
            }
            else{
                printf("Ya existe");
            }
        }

        void listar(){
            
            FILE *arch;
            arch=fopen("fichero.dat","rb");
            if (arch==NULL)
                exit(1);
            student_t estudiante;
            fread(&estudiante, sizeof(student_t), 1, arch);
            while(!feof(arch))
            {
                printf("%i %s %0.2f\n", estudiante.student_id, estudiante.NIF, estudiante.first_name, estudiante.last_name);
                fread(&producto, sizeof(tproducto), 1, arch);
            }
            fclose(arch);
            continuar();
        }
    */
}  