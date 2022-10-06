#define MAX_CHARS_NIF 9

typedef struct{
    int student_id;
    char NIF[MAX_CHARS_NIF+1];
    char* first_name;
    char* last_name;
} student_t;

/*
FILE *file;
//funcion que acepta como parametro el listado de regsitros en formato ASCII
//asi como el numero de registros y devuelve la representacion binaria de los mismos hecho con malloc()
student_t* parse_records(char* records[], int nr_records);

//vuelca al fichero binario abierto los registros de estudiastes apsados como parametro
int dump_entries(student_t* entries, int nr_entries, FILE* students);


//lee informacion de un fichero binario de registor de estudiantes y devuelve la informacion de la cabecera
//la memoria que se retorna debe reservarse con malloc() dentro de la propia funcion
student_t* read_student_file(FILE* students, int* nr_entries);

//lee una cadena de carácteres terminada en ´\0´ del fichero que se pasa por paramrtro, 
// reservando la cantidad de memoria adecuada
char* loadstr(FILE* students);
*/