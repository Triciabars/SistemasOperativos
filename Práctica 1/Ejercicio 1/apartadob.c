#include <stdio.h>
#include <stdlib.h>
#include <err.h>

int main(int argc, char* argv[]) {
	FILE* file=NULL;
	int buffer[100];
	int c,ret;
	int size= atoi(argv[2]);

	if (argc!=3) {
		fprintf(stderr,"Usage: %s <file_name> <tam>\n",argv[0]);
		exit(1);
	}

	/* Open file */
	if ((file = fopen(argv[1], "r")) == NULL)
		err(2,"The input file %s could not be opened",argv[1]);


	/* Read file byte by byte */
	while ((c = fread(buffer,size,1,file))==1) {//lee un byte cd es igual a 1
		/* Print byte to stdout */
		ret=fwrite(buffer,size,1,stdout);

		if (ret==0){//no escribe cuando ret =0
			fclose(file);
			err(4,"fwrite() failed!!");
		}
	}

	fclose(file);
	return 0;
}