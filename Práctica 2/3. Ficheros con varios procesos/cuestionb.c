#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(void)
{
    int fd1,fd2,i,pos;
    char c;
    char buffer[6];

    fd1 = open("output.txt", O_CREAT | O_TRUNC | O_RDWR, S_IRUSR | S_IWUSR); //abre fd1
    for (i=1; i < 10; i++) {
        pos = lseek(fd1, 0, SEEK_CUR); //puntero se coloca en donde estaba +0
        if (fork() == 0) { //crea hijo y hace lo de detro si ya es hijo
            /* Child */
            sprintf(buffer, "%d", i*11111);
            lseek(fd1, pos, SEEK_SET); //puntero de fd1 se posiciona en pos
            write(fd1, buffer, 5);
            close(fd1);
            exit(0); 
        } else { //padre hace lo siguiente
            /* Parent */
            lseek(fd1, 10, SEEK_CUR); //puntero se posiciona en donde estaba más 10
        }
	    write(fd1, "00000", 5);
    }

	//wait for all childs to finish
    while (wait(NULL) != -1);

    lseek(fd1, 0, SEEK_SET);
    printf("File contents are:\n");
    while (read(fd1, &c, 1) > 0)
        printf("%c", (char) c);
    printf("\n");
    close(fd1);
    exit(0);
}
