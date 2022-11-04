#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>

/* Forward declaration */
int get_size_dir(char *fname, size_t *blocks);

/* Gets in the blocks buffer the size of file fname using lstat. If fname is a
 * directory get_size_dir is called to add the size of its contents.
 */
int get_size(char *fname, size_t *blocks)
{
	struct stat *buf; 
	int size = 0;
	lstat(fname,&buf);
	if (S_ISDIR(buf->st_mode)) size = get_size_dir(fname, blocks);
	else size = buf->st_blocks;
	return size;
}


/* Gets the total number of blocks occupied by all the files in a directory. If
 * a contained file is a directory a recursive call to get_size_dir is
 * performed. Entries . and .. are conveniently ignored.
 */
int get_size_dir(char *dname, size_t *blocks)
{

	DIR *dirp;
	struct dirent *dp;
	int size = 0;
	char filename[25];
	if ((dirp = opendir(dirp)) == NULL) { perror(dirp); return 0; }
	while ((dp = readdir(dirp)) != NULL) {
		if (!strcmp(".", dp->d_name)) continue;
		if (!strcmp("..", dp->d_name)) continue;
		//sprintf(filename, "%s/%s", dir, dp->d_name);
		size += get_size(filename, 512);
	}
    closedir(dirp);
	return size;
}

/* Processes all the files in the command line calling get_size on them to
 * obtain the number of 512 B blocks they occupy and prints the total size in
 * kilobytes on the standard output
 */
int main(int argc, char *argv[])
{
	int size = 0;
	for(int i =0; i < argc; i++){
		size = get_size(argv[i], 512); //size = numero de bloques de 512B
		size = size*512/1024; //para que sean kb
		printf("%d %s\n", i, argv[i], size); //nombre de fichero   tamaño en kb //una linea por cada fichero
	}
	
	return 0;
}
//main lstat