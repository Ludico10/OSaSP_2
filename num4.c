#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	if (argc != 3)  fprintf(stderr,"Wrong number of parameters\n");
	else
	{
		int N = strtol(argv[2],NULL,10);
		if ((errno != ERANGE) && (errno != EINVAL) && (*endptr == '\0') && (N >= 0) && (strlen(argv[2]) != 0))
		{
			int op;	
			if (op = open(argv[1], O_RDONLY)) 
			{ 
				FILE *fd;
				if (fd = fdopen(op,"r")) 
				{
					char ch;		
					for (int line = 0; ch != EOF;) 
					{
						ch = getc(fd);
						while ((ch != '\n') && (ch != EOF))
						{
							if (putc(ch,stdout) == EOF)  fprintf(stderr,"Writing character error\n");
							ch = getc(fd);
							if (ch == EOF) fprintf(stderr,"Reading character error\n");
						}		
						if (ch == '\n')  
						{
							line++;
							if (putc(ch,stdout) == EOF)  fprintf(stderr,"Writing character error\n");
						}
						if ((line >= N) && (N != 0)) 
						{
							if (getc(stdin) == EOF)  fprintf(stderr,"Writing character error\n");
							line = 0;
						}	
					}
				}
				else  perror("fdopen() ");
				if (fclose(fd) != 0)  perror("fclose() ");
			}	
			else perror("open() ");
		}
		else fprintf(stderr, "Wrong 2 parameter\n");
	}
	return 0;
}
