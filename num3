#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	if (argc != 2)  fprintf(stderr,"Wrong number of parameters\n");
	else
	{
		const int stop = 6; 	//ctrl+F
		int op;
		if (op = open(argv[1], O_WRONLY | O_CREAT, 0644))	//rw-r-r
		{
			FILE* fd;
			if (fd = fdopen(op, "w")) 
			{
				char ch;
				while ((ch = getchar()) != stop) 
					if (putc(ch, fd) == EOF)  fprintf(stderr,"Writing error\n");
			}	
			else  perror("fdopen() ");
			if (fclose(fd))  perror("fclose() ");
		}	
		else  perror("open() ");
	}	
	return 0;
}
